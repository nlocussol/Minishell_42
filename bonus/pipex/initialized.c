/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialized.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:14:57 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/11 15:56:03 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	file_dup2(t_arg *arg)
{
	dup2(arg->fd[0], 0);
	dup2(arg->fd[1], 1);
}

int	total_cmd(t_tok *token)
{
	t_tok	*buf;
	int		cnt;

	cnt = 0;
	buf = token;
	while (buf != NULL)
	{
		if (buf->type == CMD || buf->type == BUILTINS_F
			|| buf->type == NOT_CMD || buf->type == BUILTINS)
			cnt++;
		buf = buf->next;
	}
	return (cnt);
}

void	initialized_f(t_arg *arg, t_tok *token)
{
	arg->bin_pipe = 0;
	arg->path = 0;
	arg->cnt = 0;
	arg->path_env = NULL;
	arg->not_file = 0;
	arg->fd = ft_calloc(2, sizeof(int));
	arg->fd[0] = 0;
	arg->fd[1] = 0;
	arg->env = set_up_tab(g_vars->env);
	arg->exit = 0;
	arg->pid = ft_calloc(sizeof(int), total_cmd(token));
	arg->path_cmd = ft_calloc(sizeof(char *), total_cmd(token) + 1);
	arg->here_doc = 0;
}

void	initialized_pipe(t_arg *arg, t_tok *token)
{
	int		i;

	i = 0;
	if (pipe(arg->here_pipe) == -1)
		print_error(3, token, NULL, arg);
	if (pipe(arg->pipe[0]) == -1)
		print_error(3, token, NULL, arg);
	if (pipe(arg->pipe[1]) == -1)
		print_error(3, token, NULL, arg);
}
