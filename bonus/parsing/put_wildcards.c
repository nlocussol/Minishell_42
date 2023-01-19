/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wildcards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:24:11 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/06 17:16:16 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_wildcards(char *cmd)
{
	int		i;
	char	*tmp;
	int		wildc;

	i = 0;
	wildc = 0;
	if (strchr(cmd, '*') != NULL
		&& ft_strchr(cmd, '/') == NULL)
	{
		tmp = wildcards(cmd);
		if (tmp != NULL)
		{
			free(cmd);
			cmd = ft_strdup(tmp);
			wildc = 1;
		}
		free(tmp);
	}
	i++;
	tmp = ft_strdup(cmd);
	free(cmd);
	return (tmp);
}
