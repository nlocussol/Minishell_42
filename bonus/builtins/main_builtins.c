/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:30:50 by averdon           #+#    #+#             */
/*   Updated: 2023/01/19 15:17:47 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_up_tab_functions(int (*tab_functions[7])(int, char **, int),
		char *tab_name[7])
{
	tab_functions[0] = &main_cd;
	tab_name[0] = "cd";
	tab_functions[1] = &main_echo;
	tab_name[1] = "echo";
	tab_functions[2] = &main_env;
	tab_name[2] = "env";
	tab_functions[3] = &main_exit;
	tab_name[3] = "exit";
	tab_functions[4] = &main_export;
	tab_name[4] = "export";
	tab_functions[5] = &main_pwd;
	tab_name[5] = "pwd";
	tab_functions[6] = &main_unset;
	tab_name[6] = "unset";
}

void	free_builtins(char ***argv, int pid, t_arg *arg)
{
	(void)arg;
	ft_free_array(*argv);
	if (pid == 0)
		free_global();
}

int	main_builtins(int argc, char **argv, int pid, t_arg *arg)
{
	int		(*tab_functions[7])(int, char **, int);
	char	*tab_name[7];
	int		i;
	int		return_value;

	set_up_tab_functions(tab_functions, tab_name);
	return_value = 0;
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(argv[0], tab_name[i]) == 0)
		{
			if (i == 3 && will_quit(argc, argv))
			{
				ft_close(arg);
				ft_free(arg);
			}
			return_value = tab_functions[i](argc, argv, pid);
			break ;
		}
		i++;
	}
	free_builtins(&argv, pid, arg);
	return (return_value);
}
