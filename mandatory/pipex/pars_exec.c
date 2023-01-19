/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:33:22 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/19 14:19:05 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_env_var(t_arg *arg, t_tok *cmd, char *first_cmd, int cnt)
{
	char	*tmp;

	arg->path_cmd[arg->cnt] = NULL;
	if (first_cmd[0] != '$' || (first_cmd[0] == '$'
			&& (first_cmd[1] == '?' || ft_strlen(first_cmd) == 1)))
	{
		cmd->type = NOT_CMD;
		arg->exit = 127;
		tmp = ft_strdup_supress_quotes(first_cmd);
		if ((cnt == 0 || ft_strchr(tmp, '/') != NULL) && tmp[0])
		{
			ft_fdprintf(2, "bash: %s: No such file or directory\n", tmp);
			free(tmp);
			free(first_cmd);
			arg->exit = 126;
			return ;
		}
		put_error(arg, cmd, tmp, first_cmd);
		free(tmp);
	}
	else
		cmd->type = VAR;
	free(first_cmd);
}

int	left_fd(t_tok *buf, t_arg *arg)
{
	if (buf->type == LEFT)
	{
		check_fd(arg->fd[0]);
		arg->fd[0] = open(buf->next->token, O_RDONLY);
		if (check_files_in(arg->fd[0], buf->next->token, buf, arg) == 1)
			return (1);
	}
	if (buf->type == HERE_DOC)
	{
		check_fd(arg->fd[0]);
		signal(CTRL_BACKSLASH, SIG_IGN);
		here_doc(arg, buf);
		signal(CTRL_BACKSLASH, ctrl_backslash);
	}
	return (0);
}

int	right_fd(t_tok *buf, t_arg *arg)
{
	if (buf->type == APPEND)
	{
		check_fd(arg->fd[1]);
		arg->fd[1] = open(buf->next->token,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (check_files_in(arg->fd[1], buf->next->token, buf, arg) == 1)
			return (1);
	}
	if (buf->type == RIGHT)
	{
		check_fd(arg->fd[1]);
		arg->fd[1] = open(buf->next->token,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (check_files_in(arg->fd[1], buf->next->token, buf, arg) == 1)
			return (1);
	}
	return (0);
}

int	access_dir(t_arg *arg, char *first_cmd, char *tmp2)
{
	DIR		*tmp;

	tmp = opendir(first_cmd);
	if (tmp != NULL)
	{
		free(tmp2);
		closedir(tmp);
		return (0);
	}
	closedir(tmp);
	arg->path_cmd[arg->cnt] = ft_strdup(tmp2);
	free(tmp2);
	free(first_cmd);
	return (1);
}

int	access_cmd(t_arg *arg, t_tok *cmd, char *first_cmd)
{
	char	*tmp2;

	if (check_builtins(cmd->token, arg) != 0)
	{
		cmd->type = 8 + check_builtins(cmd->token, arg);
		arg->path_cmd[arg->cnt] = ft_strdup(first_cmd);
		free(first_cmd);
		return (1);
	}
	if (first_cmd[0] == '"')
		tmp2 = ft_strtrim(first_cmd, "\"");
	else
		tmp2 = ft_strtrim(first_cmd, "'");
	if (access(tmp2, X_OK) == 0)
		return (access_dir(arg, first_cmd, tmp2));
	free(tmp2);
	return (0);
}
