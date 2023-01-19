/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_of_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:15:33 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 15:20:25 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_key(char *key)
{
	int				i;
	char			*key_to_check;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			break ;
		i++;
	}
	key_to_check = ft_calloc(i + 2, sizeof(char));
	key_to_check[i] = '=';
	i--;
	while (i >= 0)
	{
		key_to_check[i] = key[i];
		i--;
	}
	return (key_to_check);
}

char	*value_of_key(char *key)
{
	char			*key_to_check;
	t_double_list	*buffer;
	char			*value;

	key_to_check = parse_key(key);
	if (ft_strcmp(key, "=") == 0)
		return (ft_strdup("$"));
	key = key_to_check;
	buffer = g_vars->env;
	value = ft_strdup("");
	while (buffer)
	{
		if (ft_strncmp(buffer->content, key, ft_strlen(key)) == 0)
		{
			free(value);
			value = ft_strdup(&(((char *)(buffer->content))[ft_strlen(key)]));
		}
		buffer = buffer->next;
	}
	free(key_to_check);
	return (value);
}
