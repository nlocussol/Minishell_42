/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:19:37 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/11 14:12:56 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_calloc(char *line)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "<<", 2) || !ft_strncmp(&line[i], ">>", 2))
			cnt += 4;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			cnt += 3;
		else
			cnt++;
		i++;
	}
	return (cnt);
}

int	space(char *str, int c, int i)
{
	if (i != 0 && str[i - 1] != ' ' && (c == '|' || (c == '>'
				&& str[i - 1] != '>') || (c == '<' && str[i - 1] != '<')))
	{
		str[i] = ' ';
		i++;
	}
	str[i] = c;
	return (i);
}

void	put_space_next(char *line, char **str, size_t *i, int *i_str)
{
	if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
	{
		*i_str = space(*str, line[*i], *i_str);
		if (line[*i + 1] && line[*i + 1] != '<'
			&& line[*i + 1] != '>' && line[*i + 1] != ' ')
		{
			(*str)[*i_str + 1] = ' ';
			*i_str += 1;
		}
	}
	else
		(*str)[*i_str] = line[*i];
}

void	detect_quotes(char *line, char **str, size_t *i, int *i_str)
{
	if (line[*i] == '\"')
	{
		(*str)[*i_str] = line[*i];
		(*i_str)++;
		(*i)++;
		while (line[*i] && line[*i] != '"')
		{
			(*str)[*i_str] = line[*i];
			(*i_str)++;
			(*i)++;
		}
	}
	else if (line[*i] == '\'')
	{
		(*str)[*i_str] = line[*i];
		(*i_str)++;
		(*i)++;
		while (line[*i] && line[*i] != '\'')
		{
			(*str)[*i_str] = line[*i];
			(*i_str)++;
			(*i)++;
		}
	}
	(*str)[*i_str] = line[*i];
}

char	*put_space(char *line)
{
	size_t	i;
	int		i_str;
	char	*str;

	i = 0;
	i_str = 0;
	str = ft_calloc(len_calloc(line) + 2, 1);
	while (i < ft_strlen(line))
	{
		if (line[i] == '"' || line[i] == '\'')
			detect_quotes(line, &str, &i, &i_str);
		else
			put_space_next(line, &str, &i, &i_str);
		i_str++;
		i++;
	}
	str[i_str] = 0;
	free(line);
	return (str);
}
