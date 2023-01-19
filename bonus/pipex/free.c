/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:20:39 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/11 15:57:25 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_path_cmd(char	**str, t_arg *arg)
{
	int	i;

	i = 0;
	while (i != arg->cnt + 1)
	{
		free(str[i]);
		i++;
	}
	check_free(str);
}

void	free_split(char	**str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
		{
			check_free(str[i]);
			i++;
		}
		check_free(str);
	}
}

void	ft_free(t_arg *arg)
{
	free_path_cmd(arg->path_cmd, arg);
	free_split(arg->path_env);
	free_split(arg->env);
	check_free(arg->pid);
	check_free(arg->fd);
	check_free(arg);
}
