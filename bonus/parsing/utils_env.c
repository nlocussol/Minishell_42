/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:32:05 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/18 09:37:16 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	var_key(char *line, int *i, int *cnt)
{
	char	*tmp;

	tmp = value_of_key(&line[*i + 1]);
	*cnt += ft_strlen(tmp);
	free(tmp);
	while (line[*i + 1] && line[*i] != ' '
		&& line[*i] != '$' && ft_isalnum(line[*i]) == 1)
		(*i)++;
}

int	if_quote(char *tab, int j)
{
	j++;
	while (tab[j] != '\0')
	{
		if (tab[j] == '\'')
			return (1);
		j++;
	}
	return (0);
}

int	if_convert(char *tab)
{
	int		i;
	int		double_quotes;

	i = -1;
	double_quotes = 0;
	while (tab[++i])
	{
		if (tab[i] == '"' && double_quotes == 1)
			double_quotes = 0;
		else if (tab[i] == '"')
			double_quotes = 1;
		if (tab[i] == '\'' && if_quote(tab, i) == 1 && double_quotes != 1)
		{
			while (tab[i + 1] != '\'')
				i++;
		}
		if (tab[i] == '$' && i > 0 && ((tab[i - 1] == '\'' || tab[i - 1] == '"')
				&& (tab[i + 1] == '"' || tab[i + 1] == '\'')))
				i++;
		if (tab[i] == '$' && tab[i + 1] != '\0'
			&& tab[i + 1] != ' ' && tab[i + 1] != '"'
			&& tab[i + 1] != '\'' && tab[i + 1] != '\t')
			return (1);
	}
	return (0);
}
