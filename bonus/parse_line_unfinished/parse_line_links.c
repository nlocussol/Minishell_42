/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_links.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:31:57 by averdon           #+#    #+#             */
/*   Updated: 2023/01/13 15:14:58 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_link(char *temp)
{
	if (ft_strcmp(temp, "&&") == 0
		|| ft_strcmp(temp, "||") == 0
		|| ft_strcmp(temp, "|") == 0)
		return (1);
	return (0);
}

int	links_command_closed(char *line, int mode)
{
	char	**temp;

	line = put_space_command(line);
	temp = ft_split_quotes(line, ' ');
	free(line);
	if (check_link(temp[len_array(temp) - 1]))
	{
		if (len_array(temp) - 2 > 0 && check_link(temp[len_array(temp) - 2]))
		{
			free_split(temp);
			if (mode)
				ft_fdprintf(2, "bash: syntax error near unexpected token \
`%s'\n", temp[len_array(temp) - 2]);
			return (-1);
		}
		else
		{
			free_split(temp);
			return (1);
		}
	}
	else
	{
		free_split(temp);
		return (0);
	}
}
