/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:26:37 by averdon           #+#    #+#             */
/*   Updated: 2023/01/16 17:02:17 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	length_digit(int nb)
{
	int	length;

	length = 1;
	while (nb / 10 > 0)
	{
		nb = nb / 10;
		length = length * 10;
	}
	return (length);
}

void	free_before_exit(char *arg, char **argv, char *str)
{
	free(arg);
	free(str);
	ft_free_array(argv);
	free_global();
}

void	two_or_more_arg(int argc, char **argv)
{
	char	*str;
	int		exit_code;
	char	*arg;

	arg = parse_arg(argv[1]);
	str = ft_lltoa(ft_atoll(arg));
	if (ft_strcmp(str, arg) != 0)
	{
		ft_fdprintf(2, "bash: exit: %s: numeric argument required\n", arg);
		free_before_exit(arg, argv, str);
		exit (2);
	}
	else if (argc <= 2)
	{
		exit_code = ft_atoll(arg);
		free_before_exit(arg, argv, str);
		exit(exit_code % 256);
	}
	else
	{
		free(arg);
		free(str);
	}
}

int	main_exit(int argc, char **argv, int pid)
{
	int	exit_code;

	(void)pid;
	if (pid != 0)
		ft_fdprintf(1, "exit\n");
	if (argc == 1)
	{
		exit_code = g_vars->exit_code;
		free_global();
		if (pid != -1)
			ft_free_array(argv);
		exit (exit_code);
	}
	else
		two_or_more_arg(argc, argv);
	if (argc > 2)
		ft_fdprintf(2, "bash: exit: too many arguments\n");
	return (1);
}

int	will_quit(int argc, char **argv)
{
	char	*str;
	char	*arg;

	if (!argv[1])
		return (1);
	arg = parse_arg(argv[1]);
	str = ft_lltoa(ft_atoll(arg));
	if (argc <= 2 || ft_strcmp(str, arg) != 0)
	{
		free(str);
		free(arg);
		return (1);
	}
	else
	{
		free(str);
		free(arg);
		return (0);
	}
}
