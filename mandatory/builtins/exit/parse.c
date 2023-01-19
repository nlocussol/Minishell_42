/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:14:40 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 17:48:45 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sign_first(char **arg, int sign)
{
	char	*temp;

	if ((*arg)[0] == '-')
		sign = -1;
	temp = ft_strdup(&((*arg)[1]));
	free(*arg);
	*arg = temp;
	if ((*arg)[0] == '\'')
	{
		temp = ft_strtrim(*arg, "'");
		free(*arg);
		*arg = temp;
	}
	else if ((*arg)[0] == '"')
	{
		temp = ft_strtrim(*arg, "\"");
		free(*arg);
		*arg = temp;
	}
	if (sign == -1)
	{
		temp = ft_strjoin("-", *arg);
		free(*arg);
		*arg = temp;
	}
}

void	add_sign(char **arg, int sign)
{
	char	*temp;

	if (sign == -1)
	{
		temp = ft_strjoin("-", *arg);
		free(*arg);
		*arg = temp;
	}
}

void	quotes_first(char **arg, int sign)
{
	char	*temp;

	if ((*arg)[0] == '\'')
	{
		temp = ft_strtrim(*arg, "'");
		free(*arg);
		*arg = temp;
	}
	else if ((*arg)[0] == '"')
	{
		temp = ft_strtrim(*arg, "\"");
		free(*arg);
		*arg = temp;
	}
	if ((*arg)[0] == '-')
		sign = -1;
	if ((*arg[0]))
	{
		temp = ft_strdup(&((*arg)[1]));
		free(*arg);
		*arg = temp;
	}
	add_sign(arg, sign);
}

char	*parse_arg(char *arg)
{
	int		sign;
	char	*temp;

	sign = 1;
	arg = ft_strdup(arg);
	if (arg[0] == '+' || arg[0] == '-')
		sign_first(&arg, sign);
	else if (arg[0] == '\'' || arg[0] == '\"')
		quotes_first(&arg, sign);
	else
	{
		temp = ft_strdup(arg);
		free(arg);
		arg = temp;
	}
	return (arg);
}
