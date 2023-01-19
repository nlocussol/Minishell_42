/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <nlocusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:36:43 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/13 15:49:20 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	left_right(t_tok *token)
{
	t_tok	*buf;
	int		right;
	int		left;
	int		cmd;

	cmd = 0;
	right = 0;
	left = 0;
	buf = token;
	if (buf->prev == NULL)
		cmd = 1;
	while (buf && buf->type != PIPE)
	{
		if (buf->type == RIGHT || buf->type == APPEND)
			right = 1;
		else if (buf->type == LEFT || buf->type == HERE_DOC)
			left = 1;
		buf = buf->next;
	}
	if (cmd == 1 && right == 1 && left == 1)
		return (1);
	return (0);
}

void	dup2_bis(t_tok *token, t_arg *arg)
{
	if (token->prev && token->prev->prev
		&& (token->prev->prev->type == RIGHT
			|| token->prev->prev->type == APPEND))
		dup2(arg->fd[1], 1);
	else if ((token->prev->type == FILES || token->prev->type == LIMITER)
		&& token->next == NULL && fd_exit(arg->fd[0]) == 0)
		dup2(arg->fd[0], 0);
	else if (token->prev->type == PIPE && token->next == NULL)
		dup2(arg->pipe[(arg->cnt + 1) % 2][0], 0);
	else if (token->prev->type == PIPE && (token->next->type == RIGHT
			|| token->next->type == APPEND) && fd_exit(arg->fd[1]) == 0)
		right_dup2(arg);
	else if (token->prev->type == PIPE && (token->next->type == LEFT
			|| token->next->type == HERE_DOC) && fd_exit(arg->fd[1]) == 0
		&& if_pipe(token) == 0)
		dup2(arg->fd[0], 0);
	else if (token->prev->type == PIPE && (token->next->type == LEFT
			|| token->next->type == HERE_DOC) && fd_exit(arg->fd[1]) == 0
		&& if_pipe(token) == 1)
		left_dup2(arg);
	else if ((token->prev->type == FILES || token->prev->type == LIMITER)
		&& token->next->type == PIPE && fd_exit(arg->fd[0]) == 0)
		left_dup2(arg);
	else if (token->prev->type == PIPE && token->next->type == PIPE)
		other_dup2(arg);
}

void	do_dup2(t_tok *token, t_arg *arg)
{
	if (token->prev == NULL && token->next == NULL)
		return ;
	else if (token->prev == NULL && token->next->type == PIPE)
		dup2(arg->pipe[arg->cnt % 2][1], 1);
	else if (token->prev == NULL && (token->next->type == RIGHT
			|| token->next->type == APPEND) && fd_exit(arg->fd[1]) == 0)
		dup2(arg->fd[1], 1);
	else if (token->prev == NULL && (token->next->type == LEFT
			|| token->next->type == HERE_DOC) && if_pipe(token) == 0
		&& if_right(token) != 1 && fd_exit(arg->fd[0]) == 0)
		dup2(arg->fd[0], 0);
	else if (left_right(token) == 1)
		file_dup2(arg);
	else if (token->prev == NULL && (token->next->type == LEFT
			|| token->next->type == HERE_DOC) && if_pipe(token) == 1
		&& fd_exit(arg->fd[0]) == 0)
		left_dup2(arg);
	else if (token->prev->type == LIMITER && token->next == NULL)
		dup2(arg->fd[0], 0);
	else if (token->next && fd_exit(arg->fd[1]) == 0 && fd_exit(arg->fd[0]) == 0
		&& (token->prev->type == FILES || token->prev->type == LIMITER)
		&& (token->next->type == RIGHT || token->next->type == APPEND))
		file_dup2(arg);
	else
		dup2_bis(token, arg);
}
