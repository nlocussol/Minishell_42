/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:04:47 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/10 15:12:54 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	left_dup2(t_arg *arg)
{
	dup2(arg->fd[0], 0);
	dup2(arg->pipe[0][1], 1);
}

void	right_dup2(t_arg *arg)
{
	dup2(arg->pipe[(arg->cnt + 1) % 2][0], 0);
	dup2(arg->fd[1], 1);
}

void	other_dup2(t_arg *arg)
{
	dup2(arg->pipe[(arg->cnt + 1) % 2][0], 0);
	dup2(arg->pipe[arg->cnt % 2][1], 1);
}

void	tok_clear(t_tok *tok)
{
	while (tok->prev)
		tok = tok->prev;
	ft_tokclear(&tok, del_tok);
}
