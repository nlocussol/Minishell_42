/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:15:47 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 17:53:01 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c_exec_and_heredoc(int signum)
{
	(void)signum;
	g_vars->ctrl_c = 1;
	close(0);
	rl_replace_line("", 1);
	ft_fdprintf(1, "\n");
	rl_on_new_line();
	g_vars->exit_code = 130;
}

void	ctrl_c_classic(int signum)
{
	(void)signum;
	g_vars->ctrl_c = 1;
	rl_replace_line("", 1);
	ft_fdprintf(1, "\n");
	rl_on_new_line();
	rl_redisplay();
	g_vars->exit_code = 130;
}

void	ctrl_c_here_doc(int signum)
{
	(void)signum;
	g_vars->ctrl_c = 1;
	close(0);
	rl_replace_line("", 1);
	ft_fdprintf(1, "\n");
	rl_on_new_line();
	g_vars->exit_code = 130;
}

void	ctrl_backslash(int signum)
{
	(void)signum;
	ft_fdprintf(2, "Quit (core dumped)\n");
	g_vars->exit_code = 131;
}

void	ctrl_c_exec_start(int signum)
{
	(void)signum;
	g_vars->ctrl_c = 1;
	rl_replace_line("", 1);
	ft_fdprintf(1, "\n");
	rl_on_new_line();
	g_vars->exit_code = 130;
}
