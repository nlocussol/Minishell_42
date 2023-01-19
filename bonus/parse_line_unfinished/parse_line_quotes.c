/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:31:40 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 17:37:12 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	modify_quotes(char c, int *double_opened, int *single_opened)
{
	if (c == '\'')
	{
		if (!(*double_opened))
		{
			if (!(*single_opened))
				*single_opened = 1;
			else
				*single_opened = 0;
		}
	}
	if (c == '"')
	{
		if (!(*single_opened))
		{
			if (!(*double_opened))
				*double_opened = 1;
			else
				*double_opened = 0;
		}
	}
}

int	quotes_closed(char *command)
{
	int	i;
	int	single_opened;
	int	double_opened;

	i = 0;
	single_opened = 0;
	double_opened = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
			modify_quotes(command[i], &double_opened, &single_opened);
		i++;
	}
	if (single_opened || double_opened)
		return (1);
	else
		return (0);
}
