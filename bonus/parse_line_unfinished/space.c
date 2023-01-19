/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:33:07 by averdon           #+#    #+#             */
/*   Updated: 2023/01/16 14:57:43 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_new_line(char **new_line, char *temp)
{
	char	*temp_str;

	if (!(*new_line))
		*new_line = ft_strdup(temp);
	else
	{
		temp_str = ft_strjoin(*new_line, temp);
		free(*new_line);
		*new_line = temp_str;
	}
}

void	add_space_command(char **temp, int i)
{
	char	*temp_str;

	temp_str = put_space(temp[i]);
	if (temp[i + 1])
		temp[i] = ft_strjoin(temp_str, " ");
	else
		temp[i] = ft_strdup(temp_str);
	free(temp_str);
}

char	*put_space_parsing(char *line)
{
	char	*temp_str;
	char	**temp;
	char	*new_line;
	int		i;

	temp_str = put_space_command(line);
	temp = ft_split_quotes(temp_str, ' ');
	free(temp_str);
	new_line = NULL;
	i = 0;
	while (temp[i])
	{
		if (ft_strcmp(temp[i], "&&") != 0
			&& ft_strcmp(temp[i], "||") != 0)
			add_space_command(temp, i);
		create_new_line(&new_line, temp[i]);
		i++;
	}
	free_split(temp);
	free(line);
	return (new_line);
}
