/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:21:14 by averdon           #+#    #+#             */
/*   Updated: 2023/01/19 15:24:41 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_next(t_double_list *buffer)
{
	if (ft_strcmp(buffer->next->content, "&&") != 0
		&& ft_strcmp(buffer->content, "&&") != 0
		&& ft_strcmp(buffer->next->content, "||") != 0
		&& ft_strcmp(buffer->content, "||") != 0)
		return (1);
	return (0);
}

void	copy_and_skip_quotes(char **new_line, char *str, int *i, int *j)
{
	if (str[*i] == '\'')
	{
		(*new_line)[*j] = str[*i];
		(*i)++;
		(*j)++;
		while (str[*i] && str[*i] != '\'')
		{
			(*new_line)[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
	else if (str[*i] == '\"')
	{
		(*new_line)[*j] = str[*i];
		(*i)++;
		(*j)++;
		while (str[*i] && str[*i] != '\"')
		{
			(*new_line)[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
	}
}

int	count_nb_to_add(char *str)
{
	int	i;
	int	nb_char_add;

	i = 0;
	nb_char_add = 0;
	while (str[i])
	{
		if (str[i + 1] && ((str[i] == '|' && str[i + 1] == '|')
				|| (str[i] == '&' && str[i + 1] == '&')))
			nb_char_add += 2;
		i++;
	}
	return (nb_char_add);
}

void	add_space(char **new_line, char *str, int i, int *j)
{
	if (str[i] && str[i + 1])
	{
		if ((str[i + 1] == '&' && str[i] == '&')
			|| (str[i + 1] == '|' && str[i] == '|'))
		{
			(*new_line)[*j] = ' ';
			(*j)++;
		}
	}
	(*new_line)[*j] = str[i];
	if (i > 0)
	{
		if ((str[i - 1] == '&' && str[i] == '&')
			|| (str[i - 1] == '|' && str[i] == '|'))
		{
			(*j)++;
			(*new_line)[*j] = ' ';
		}
	}
}

void	reload_split_command(char *command)
{
	char					*temp;

	temp = ft_strdup(command);
	split_command(&temp, 0);
}
