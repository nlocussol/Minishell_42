/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:54:43 by averdon           #+#    #+#             */
/*   Updated: 2023/01/19 13:28:59 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_old_pwd(char *pwd, int pid)
{
	char			*str_temp;
	char			*temp[2];

	temp[0] = "export";
	str_temp = value_of_key("OLDPWD");
	if (str_temp && str_temp[0])
	{
		temp[1] = ft_strjoin("OLDPWD=", pwd);
		main_export(2, temp, pid);
		free(temp[1]);
	}
	free(str_temp);
}

void	update_pwd(char *new_path, int pid)
{
	char			*str_temp;
	char			*temp[2];

	temp[0] = "export";
	str_temp = value_of_key("PWD");
	if (str_temp && str_temp[0])
	{
		temp[1] = ft_strjoin("PWD=", new_path);
		main_export(2, temp, pid);
		free(temp[1]);
	}
	free(str_temp);
}

void	go_back(char *pwd, int pid)
{
	char			*new_path;

	new_path = ft_strcut_end(pwd, '/');
	if (new_path && !new_path[0])
	{
		free(new_path);
		new_path = ft_strdup("/");
	}
	chdir(new_path);
	update_pwd(new_path, pid);
	free(new_path);
}

int	return_home(int pid)
{
	char	*temp[2];
	int		return_value;

	temp[0] = ft_strdup("cd");
	temp[1] = value_of_key("HOME");
	if (!home_set())
	{
		ft_fdprintf(2, "bash: cd: HOME not set\n");
		free(temp[0]);
		free(temp[1]);
		return (1);
	}
	else
	{
		return_value = main_cd(2, temp, pid);
		free(temp[0]);
		free(temp[1]);
		return (return_value);
	}
}

void	return_root(char **pwd, int pid)
{
	while (ft_strcmp(*pwd, "/") != 0)
	{
		getcwd(*pwd, 4096);
		go_back(*pwd, pid);
	}
}
