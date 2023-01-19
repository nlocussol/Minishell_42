/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:19:52 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/17 16:32:56 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_exit_code(t_arg *arg, t_tok *buf, int status)
{
	if (arg->exit == 130)
		return ;
	if (buf->type == VAR)
		arg->exit = 0;
	else if (WIFEXITED(status) && (buf->type == CMD
			|| buf->type == BUILTINS_F))
		arg->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && (buf->type == CMD
			|| buf->type == BUILTINS_F)
		&& g_vars->exit_code != 130 && g_vars->exit_code != 131)
		arg->exit = WTERMSIG(status);
	else if (g_vars->exit_code == 130 || g_vars->exit_code == 131)
		arg->exit = g_vars->exit_code;
}

void	wait_pid(t_arg *arg, t_tok *token)
{
	int		status;
	int		cnt;
	t_tok	*buf;

	cnt = 0;
	status = 0;
	buf = token;
	while (cnt != total_cmd(token))
	{
		while (buf->type != CMD && buf->type != BUILTINS_F
			&& buf->type != NOT_CMD && buf->type != BUILTINS)
			buf = buf->next;
		waitpid(arg->pid[cnt], &status, 0);
		put_exit_code(arg, buf, status);
		cnt++;
	}
}

void	print_error(int error_type, t_tok *token, char *cmd, t_arg *arg)
{
	char	*join;

	if (error_type == 0 && ft_strcmp(cmd, "exit") != 0)
	{
		ft_fdprintf(2, "%s: command not found\n", cmd);
		arg->exit = 127;
	}
	else if (error_type == 1)
	{
		ft_fdprintf(2, "bash: %s: Is a directory\n", cmd);
		arg->exit = 126;
	}
	else if (error_type == 3)
		perror("bash");
	else if (error_type == 4)
	{
		join = ft_strjoin("bash: ", token->next->token);
		perror(join);
		check_free(join);
	}
}

int	main_pipex(t_tok *token, t_double_list **boolean, t_double_list **commands)
{
	t_arg	*arg;
	int		exit_code;
	char	**tmp;

	arg = ft_calloc(sizeof(t_arg), 1);
	initialized_f(arg, token);
	tmp = set_up_tab(g_vars->env);
	split_path(arg, tmp);
	free_split(tmp);
	initialized_pipe(arg, token);
	exe_cmd(arg, token, boolean, commands);
	exit_code = arg->exit;
	ft_free(arg);
	return (exit_code);
}
