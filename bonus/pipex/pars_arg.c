/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:08:50 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/07 15:24:47 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		while (j != (int)ft_strlen(tab[i]))
		{
			if (tab[i][j] == '$' && ft_strlen(&tab[i][j]) > 1
				&& tab[i][j + 1] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	find_path(t_arg *arg, char **envp)
{
	int	cnt;

	cnt = 0;
	while (envp[cnt] != NULL)
	{
		if (ft_strncmp(envp[cnt], "PATH=", 5) == 0)
		{
			arg->path = cnt;
			return ;
		}
		cnt++;
	}
}

void	split_path(t_arg *arg, char **envp)
{
	char	*path;

	find_path(arg, envp);
	path = ft_strchr(envp[arg->path], '/');
	if (path != NULL)
		arg->path_env = ft_split(path, ':');
	else
		arg->path_env = ft_calloc(sizeof(char *), 1);
}
