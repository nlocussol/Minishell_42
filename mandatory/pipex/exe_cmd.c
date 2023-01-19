/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:19:26 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/19 15:08:33 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

void	cmd_path(t_arg *arg, t_tok *cmd)
{
	int		cnt;
	char	*tmp;
	char	*first_cmd;
	char	*tmp2;

	cnt = -1;
	first_cmd = ft_strtok(cmd->token, ' ');
	if (first_cmd == NULL || access_cmd(arg, cmd, first_cmd) == 1)
		return ;
	tmp2 = ft_strdup_supress_quotes(first_cmd);
	while (arg->path_env[++cnt] != NULL && tmp2 && tmp2[0])
	{
		tmp = ft_strjoin(arg->path_env[cnt], "/");
		arg->path_cmd[arg->cnt] = ft_strjoin(tmp, tmp2);
		check_free(tmp);
		if (access(arg->path_cmd[arg->cnt], X_OK) == 0)
		{
			free(tmp2);
			free(first_cmd);
			return ;
		}
		check_free(arg->path_cmd[arg->cnt]);
	}
	free(tmp2);
	exit_env_var(arg, cmd, first_cmd, cnt);
}

int	do_here_doc(t_tok *token, t_arg *arg, char *line, int fd)
{	
	check_limiter(line, arg, token);
	while (ft_strcmp(line, token->next->token))
	{
		line = readline("> ");
		if (check_sign(token, arg, line, fd) == 1)
			return (1);
		check_limiter(line, arg, token);
	}
	return (0);
}

void	here_doc(t_arg *arg, t_tok *token)
{
	char	*line;
	int		fd;

	signal(CTRL_C, ctrl_c_here_doc);
	close(arg->here_pipe[0]);
	close(arg->here_pipe[1]);
	if (pipe(arg->here_pipe) == -1)
		print_error(3, token, NULL, arg);
	fd = dup(0);
	line = readline("> ");
	arg->fd[0] = -1;
	if (check_sign(token, arg, line, fd) == 1)
		return ;
	else if (do_here_doc(token, arg, line, fd) == 1)
		return ;
	close(fd);
	arg->fd[0] = arg->here_pipe[0];
}

void	create_pipe(t_arg *arg, t_tok **token,
		t_double_list **boolean, t_double_list **commands)
{
	check_type(token, arg);
	if (g_vars->ctrl_c == 1)
		return ;
	if (arg->not_file == 1)
	{
		void_fork(arg, *token, boolean, commands);
		return ;
	}
	if ((*token)->type != CMD)
		return ;
	if (arg->cnt >= 2)
	{
		close(arg->pipe[arg->cnt % 2][0]);
		close(arg->pipe[arg->cnt % 2][1]);
		if (pipe(arg->pipe[arg->cnt % 2]) == -1)
			print_error(3, *token, NULL, arg);
	}
	cmd_path(arg, *token);
	arg->pid[arg->cnt] = fork();
	if ((*token)->type == BUILTINS)
		child_builtins(arg, token, boolean, commands);
	else if (arg->pid[arg->cnt] == 0)
		child_program(arg, *token, boolean, commands);
}

void	exe_cmd(t_arg *arg, t_tok *token,
		t_double_list **boolean, t_double_list **commands)
{
	t_tok	*buf;

	buf = token;
	g_vars->ctrl_c = 0;
	arg->bin_pipe = if_pipe(token);
	while (buf != NULL)
	{
		if (g_vars->ctrl_c == 1)
			break ;
		create_pipe(arg, &buf, boolean, commands);
		arg->cnt++;
		buf = buf->next;
		while (buf != NULL && buf->type != PIPE)
			buf = buf->next;
	}
	ft_close(arg);
	wait_pid(arg, token);
}
