/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <nlocusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:37:55 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/11 10:29:47 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env(t_tok *tok)
{
	t_tok	*buf;
	char	*tmp;
	char	*tmp2;

	buf = tok;
	while (buf != NULL)
	{
		tmp2 = put_wildcards(buf->token);
		tmp = convert_env(tmp2, 0, 0);
		free(tmp2);
		buf->token = ft_strdup(tmp);
		free(tmp);
		buf = buf->next;
	}
}

void	join_cmd_and_cmd_next(char **line, t_tok *tmp)
{
	char	*tmp2;

	tmp2 = ft_strjoin(*line, " ");
	free(*line);
	*line = ft_strjoin(tmp2, tmp->next->token);
	free(tmp2);
}

void	join_cmd2(t_tok *tok)
{
	t_tok	*buf;
	t_tok	*tmp;
	char	*line;

	buf = tok;
	while (buf->next != NULL)
	{
		if (buf->type == CMD)
		{
			tmp = buf;
			line = ft_strdup(buf->token);
			while (tmp->next != NULL && tmp->next->type != PIPE)
			{
				if (tmp->next->type == CMD)
					join_cmd_and_cmd_next(&line, tmp);
				tmp = tmp->next;
			}
			free(buf->token);
			buf->token = line;
		}
		buf = buf->next;
	}
}

void	join_cmd(t_tok **tok)
{
	t_tok	*buf;
	char	*tmp;
	void	*tmp2;

	buf = *tok;
	while (buf->next)
	{
		tmp2 = buf->next;
		if (buf->next && buf->next->type == CMD && buf->type == CMD)
		{
			tmp = ft_strjoin(" ", buf->next->token);
			free(buf->next->token);
			buf->next->token = ft_strjoin(buf->token, tmp);
			free(tmp);
			if (buf->prev)
				buf->prev->next = buf->next;
			buf->next->prev = buf->prev;
			ft_tokdelone(buf, del_tok);
		}
		buf = tmp2;
		if (buf->prev == NULL)
			*tok = buf;
	}
}

int	find_type(char *tok)
{
	if (ft_strcmp(tok, "<") == 0)
		return (LEFT);
	else if (ft_strcmp(tok, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(tok, ">") == 0)
		return (RIGHT);
	else if (ft_strcmp(tok, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(tok, "|") == 0)
		return (PIPE);
	else
		return (CMD);
}
