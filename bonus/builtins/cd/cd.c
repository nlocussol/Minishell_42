/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:55:49 by averdon           #+#    #+#             */
/*   Updated: 2023/01/19 13:37:43 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	home_set(void)
{
	t_double_list	*buffer;

	buffer = g_vars->env;
	while (buffer)
	{
		if (ft_strncmp(buffer->content, "HOME", 4) == 0)
			return (1);
		buffer = buffer->next;
	}
	return (0);
}

int	try_go_to_path(char **argv, char **pwd, char **old_pwd, int pid)
{
	DIR	*dir;

	dir = opendir(argv[1]);
	if (dir)
	{
		closedir(dir);
		update_old_pwd(*old_pwd, pid);
		free(*old_pwd);
		chdir(argv[1]);
		getcwd(*pwd, 4096);
		update_pwd(*pwd, pid);
		free(*pwd);
		return (0);
	}
	else
	{
		free(*old_pwd);
		ft_fdprintf(2, "bash: cd: %s: No such file or directory\n", argv[1]);
		free(*pwd);
		return (1);
	}
}

int	try_to_return_home(char **old_pwd, char **pwd, int pid)
{
	if (!home_set())
	{
		ft_fdprintf(2, "bash: cd: HOME not set\n");
		free(*old_pwd);
		free(*pwd);
		return (1);
	}
	update_old_pwd(*old_pwd, pid);
	free(*old_pwd);
	free(*pwd);
	return (return_home(pid));
}

int	main_cd(int argc, char **argv, int pid)
{
	char	*pwd;
	char	*old_pwd;

	pwd = ft_calloc(4097, sizeof(char));
	getcwd(pwd, 4096);
	old_pwd = ft_strdup(pwd);
	if (argc == 1)
		return (try_to_return_home(&old_pwd, &pwd, pid));
	else if (argc == 2)
		return (try_go_to_path(argv, &pwd, &old_pwd, pid));
	else
	{
		free(old_pwd);
		ft_fdprintf(2, "bash: cd: too many arguments\n");
		free(pwd);
		return (1);
	}
}
