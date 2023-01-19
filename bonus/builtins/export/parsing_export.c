/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:51:34 by averdon           #+#    #+#             */
/*   Updated: 2023/01/19 13:54:05 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_key(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		free(key);
		return (0);
	}
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			free(key);
			return (0);
		}
		i++;
	}
	free(key);
	return (1);
}

int	arg_valid(char *arg)
{
	char	*key;
	int		has_an_equal;

	key = ft_strdup(arg);
	if (ft_strchr(key, '='))
		has_an_equal = 1;
	else
		has_an_equal = 0;
	key[ft_strlen(key) - ft_strlen(ft_strchr(key, '='))] = '\0';
	if (ft_strlen(key) > 0 && key[ft_strlen(key) - 1] == '+')
	{
		if (has_an_equal)
			key[ft_strlen(key) - 1] = '\0';
		else
		{
			free(key);
			return (0);
		}
	}
	return (check_key(key));
}
