/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:35:02 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/17 15:21:59 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_malloc(char *line)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			cnt += 4;
			i += 2;
		}
		else if (line[i] == '$' && ft_strlen(&line[i + 1]) > 1)
			var_key(line, &i, &cnt);
		else
			cnt++;
		if (line[i])
			i++;
	}
	return (cnt);
}

void	put_env(char *tab, char *tmp, size_t *j, int *j_cp)
{
	char	*tmp2;
	char	*key;

	key = value_of_key(&tab[*j + 1]);
	*j_cp += ft_strlen(key) - 1;
	tmp2 = ft_strjoin(tmp, key);
	free(key);
	ft_strlcpy(tmp, tmp2, ft_strlen(tmp2) + 1);
	free(tmp2);
	if (tab[*j] == '$' && !ft_isalpha(tab[*j + 1]) && tab[*j + 1] != '_')
	{
		(*j)++;
		return ;
	}
	while (tab[*j + 1]
		&& (ft_isalnum(tab[*j + 1]) == 1 || tab[*j + 1] == '_'))
		(*j)++;
}

void	put_env_var(char *tab, char *tmp, size_t *j, int *j_cp)
{
	char	*tmp2;
	char	*key;

	if (tab[*j] == '$' && tab[*j + 1] == '?')
	{
		key = ft_itoa(g_vars->exit_code);
		*j_cp += ft_strlen(key) - 1;
		tmp2 = ft_strjoin(tmp, key);
		ft_strlcpy(tmp, tmp2, ft_strlen(tmp2) + 1);
		free(key);
		free(tmp2);
		(*j)++;
	}
	else if (tab[*j] == '$' && ft_strlen(tab) > 1 && tab[*j + 1] != '"'
		&& tab[*j + 1] != '\'' && tab[*j + 1] != '\0' && tab[*j + 1] != ' '
		&& tab[*j + 1] != '\t')
		put_env(tab, tmp, j, j_cp);
	else
		tmp[*j_cp] = tab[*j];
}

void	single_skip(char *tab, char *tmp, size_t *j, int *j_cp)
{
	while (tab[*j + 1] && tab[*j + 1] != '\'')
	{
		(*j)++;
		tmp[*j_cp] = tab[*j];
		(*j_cp)++;
	}
	(*j)++;
	(*j_cp)--;
}

char	*convert_env(char *tab, size_t j, int j_cp)
{
	char	*tmp;
	int		double_quotes;

	double_quotes = 0;
	if (ft_strchr(tab, '$') == NULL || if_convert(tab) == 0)
		return (ft_strdup(tab));
	tmp = ft_calloc(len_malloc(tab) + 1, 1);
	while (j < ft_strlen(tab))
	{
		if (tab[j] == '"' && double_quotes == 1)
			double_quotes = 0;
		else if (tab[j] == '"')
			double_quotes = 1;
		if (tab[j] == '\'' && if_quote(tab, j) == 1 && double_quotes != 1)
			single_skip(tab, tmp, &j, &j_cp);
		else if (tab[j] == '$')
			put_env_var(tab, tmp, &j, &j_cp);
		else
			tmp[j_cp] = tab[j];
		j++;
		j_cp++;
	}
	tab = ft_strdup(tmp);
	free(tmp);
	return (tab);
}
