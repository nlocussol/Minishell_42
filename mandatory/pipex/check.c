/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <nlocusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:14:21 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/19 14:51:22 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	void_fork(t_arg *arg, t_tok *tok, t_double_list **boolean,
		t_double_list **commands)
{
	int	i;

	i = total_cmd(tok);
	if (i > 0)
	{
		arg->pid[arg->cnt] = fork();
		if (arg->pid[arg->cnt] == 0)
		{
			ft_close(arg);
			free_global();
			ft_free(arg);
			while (tok->prev)
				tok = tok->prev;
			ft_tokclear(&tok, del_tok);
			ft_double_lstclear(boolean, del);
			ft_double_lstclear(commands, del);
			exit(1);
		}
	}
}

void	check_fd(int fd)
{
	if (fd && fd != -1 && fd != 0)
		close(fd);
}

void	ft_close(t_arg *arg)
{
	check_fd(arg->here_pipe[0]);
	check_fd(arg->here_pipe[1]);
	check_fd(arg->pipe[0][0]);
	check_fd(arg->pipe[0][1]);
	check_fd(arg->pipe[1][0]);
	check_fd(arg->pipe[1][1]);
	check_fd(arg->fd[0]);
	check_fd(arg->fd[1]);
}

void	check_limiter(char *line, t_arg *arg, t_tok *token)
{
	if (ft_strlen(line) == 1)
	{
		ft_putstr_fd(line, arg->here_pipe[1]);
		ft_putstr_fd("\n", arg->here_pipe[1]);
	}
	else if (ft_strcmp(line, token->next->token))
	{
		ft_putstr_fd(line, arg->here_pipe[1]);
		ft_putstr_fd("\n", arg->here_pipe[1]);
	}
}

int	check_builtins(char *cmd, t_arg *arg)
{
	char	*str;
	int		mode;

	mode = 0;
	str = ft_strtok(cmd, ' ');
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "exit")
		|| (!ft_strncmp(str, "export", 6) && ft_strlen(cmd) > 7))
	{
		mode = 1;
		if (arg->bin_pipe == 1)
			mode = 2;
	}
	else if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export"))
		mode = 2;
	free(str);
	return (mode);
}
