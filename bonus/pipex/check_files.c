/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:18:16 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/18 09:26:31 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_type(t_tok **tok, t_arg *arg)
{
	t_tok	*buf;

	buf = *tok;
	arg->not_file = 0;
	while (buf->next != NULL && buf->next->type != PIPE)
	{
		if (left_fd(buf, arg) == 1)
			break ;
		if (right_fd(buf, arg) == 1)
			break ;
		if (g_vars->ctrl_c == 1)
		{
			arg->cnt--;
			return ;
		}
		buf = buf->next;
	}
	while ((*tok)->next != NULL && (*tok)->next->type != PIPE
		&& (*tok)->type != CMD)
		*tok = (*tok)->next;
	if ((*tok)->type != CMD)
		arg->cnt--;
}

int	check_files_in(int fd, char *filename, t_tok *tok, t_arg *arg)
{
	if (fd == -1 || access(filename, R_OK) == -1)
	{
		tok->next->type = NOT_FILE;
		print_error(4, tok, NULL, arg);
		arg->exit = 1;
		arg->not_file = 1;
		return (1);
	}
	return (0);
}

int	check_files_out(int fd, char *filename, t_tok *tok, t_arg *arg)
{
	if (fd == -1 || access(filename, W_OK) == -1)
	{
		tok->next->type = NOT_FILE;
		print_error(4, tok, NULL, arg);
		arg->exit = 1;
		arg->not_file = 1;
		return (1);
	}
	return (0);
}

int	if_right(t_tok *tok)
{
	t_tok	*buf;

	buf = tok;
	while (buf != NULL && buf->type != PIPE)
	{
		if (buf->type == RIGHT || buf->type == APPEND)
			return (1);
		buf = buf->next;
	}
	return (0);
}

int	if_pipe(t_tok *token)
{
	t_tok	*buf;

	buf = token;
	while (buf != NULL)
	{
		if (buf->type == PIPE)
			return (1);
		buf = buf->next;
	}
	return (0);
}
