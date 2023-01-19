/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_parenthesis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:32:18 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 17:35:25 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parenthesis(int parenthesis, int mode)
{
	if (parenthesis != 0)
	{
		if (parenthesis < 0)
		{
			if (mode)
				ft_fdprintf(2, "bash: syntax error near unexpected token `)'\n");
			return (-1);
		}
		else
			return (1);
	}
	else
		return (0);
}

int	paranthesis_closed(char *line, int mode)
{
	int	i;
	int	parenthesis;

	i = 0;
	parenthesis = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += skip_quotes(&line[i]);
		else if (line[i] == '(')
			parenthesis++;
		else if (line[i] == ')')
			parenthesis--;
		if (line[i] == '(' && line[i + 1] == ')')
		{
			parenthesis = -1;
			break ;
		}
		i++;
	}
	return (check_parenthesis(parenthesis, mode));
}
