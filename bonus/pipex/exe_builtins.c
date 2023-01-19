/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:48:19 by averdon           #+#    #+#             */
/*   Updated: 2023/01/19 15:44:05 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_sign(t_tok *token, t_arg *arg, char *line, int fd)
{
	if (g_vars->ctrl_c == 1)
	{
		arg->exit = 130;
		dup2(fd, 0);
		close(fd);
		return (1);
	}
	else if (!line)
	{
		ft_fdprintf(2, "bash: warning: here-document at line 1 delimited \
by end-of-file (wanted `%s')\n", token->next->token);
		arg->fd[0] = arg->here_pipe[0];
		close(fd);
		return (1);
	}
	return (0);
}

void	free_all(t_arg *arg, t_tok *token,
		t_double_list **boolean, t_double_list **commands)
{
	ft_close(arg);
	free_global();
	ft_free(arg);
	tok_clear(token);
	ft_double_lstclear(boolean, del);
	ft_double_lstclear(commands, del);
}

void	child_program(t_arg *arg, t_tok *token,
		t_double_list **boolean, t_double_list **commands)
{
	char	**cmd;
	int		code;

	cmd = ft_split_quotes((token)->token, ' ');
	if (token->type != NOT_CMD)
		do_dup2(token, arg);
	if (token->type == BUILTINS_F)
	{
		tok_clear(token);
		ft_double_lstclear(boolean, del);
		ft_double_lstclear(commands, del);
		code = main_builtins(len_array(cmd), cmd, arg->pid[arg->cnt], arg);
		ft_close(arg);
		ft_free(arg);
		exit(code);
	}
	else if (token->type != NOT_CMD)
	{
		cmd = trim_arg(cmd);
		ft_close(arg);
		execve(arg->path_cmd[arg->cnt], cmd, arg->env);
	}
	free_split(cmd);
	free_all(arg, token, boolean, commands);
	exit(EXIT_FAILURE);
}

void	child_builtins(t_arg *arg, t_tok **token,
		t_double_list **boolean, t_double_list **commands)
{
	char	**cmd;

	cmd = ft_split_quotes((*token)->token, ' ');
	if (arg->pid[arg->cnt] == 0)
	{
		ft_free_array(cmd);
		ft_close(arg);
		free_global();
		ft_free(arg);
		tok_clear(*token);
		ft_double_lstclear(boolean, del);
		ft_double_lstclear(commands, del);
		exit(1);
	}
	if (arg->bin_pipe == 1)
		free_split(cmd);
	if (arg->bin_pipe == 1)
		return ;
	if (!ft_strcmp(cmd[0], "exit") && will_quit(len_array(cmd), cmd))
	{
		tok_clear(*token);
		ft_double_lstclear(boolean, del);
		ft_double_lstclear(commands, del);
	}
	arg->exit = main_builtins(len_array(cmd), cmd, arg->pid[arg->cnt], arg);
}
