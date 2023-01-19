/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:55:20 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/17 16:26:32 by nlocusso         ###   ########.fr       */
/*   Updated: 2022/12/15 20:28:17 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_filename(t_tok *buf)
{
	if (buf->type == PIPE)
		return (0);
	if (buf->next->type == HERE_DOC || buf->next->type == RIGHT
		|| buf->next->type == LEFT || buf->next->type == APPEND)
		return (1);
	return (0);
}

int	pars_file(t_tok *token)
{
	t_tok	*buf;

	buf = token;
	while (buf != NULL)
	{
		if ((buf->type == RIGHT || buf->type == LEFT || buf->type == APPEND
				|| buf->type == HERE_DOC) && buf->next == NULL)
		{
			ft_fdprintf(2, "bash: syntax error near unexpected \
token `newline'\n");
			return (1);
		}
		if (((buf->type == RIGHT || buf->type == LEFT || buf->type == APPEND
					|| buf->type == HERE_DOC || buf->type == PIPE)
				&& (buf->next->type == PIPE || check_filename(buf) == 1))
			|| (buf->type == PIPE && (buf->next == NULL || buf->prev == NULL)))
		{
			ft_fdprintf(2, "bash: syntax error near unexpected \
token `%s'\n", buf->token);
			return (1);
		}
		buf = buf->next;
	}
	return (0);
}	

void	trim_file(t_tok *token)
{
	t_tok	*buf;
	char	*tmp;

	buf = token;
	while (buf != NULL)
	{
		if (buf->type != CMD)
		{
			tmp = ft_strdup_supress_quotes(buf->token);
			free(buf->token);
			buf->token = tmp;
		}
		buf = buf->next;
	}
}

void	change_type(t_tok *token)
{
	t_tok	*buf;

	buf = token;
	change_env(token);
	while (buf->next != NULL)
	{
		if (buf->type == HERE_DOC && buf->next->type != PIPE
			&& check_filename(buf) != 1)
			buf->next->type = LIMITER;
		if ((buf->type == LEFT || buf->type == APPEND || buf->type == RIGHT)
			&& buf->next->type != PIPE && check_filename(buf) != 1)
			buf->next->type = FILES;
		buf = buf->next;
	}
}

void	type_tok(char *line, t_double_list **booleans, t_double_list **commands)
{
	t_tok	*new_token;
	t_tok	*token;
	char	*tok;
	int		type;

	token = NULL;
	tok = ft_strtok(line, ' ');
	type = find_type(tok);
	while (tok != NULL)
	{
		new_token = ft_toknew(tok, type);
		ft_tokadd_back(&token, new_token);
		tok = ft_strtok(NULL, ' ');
		if (tok != NULL)
			type = find_type(tok);
	}
	free(line);
	change_type(token);
	join_cmd(&token);
	trim_file(token);
	if (pars_file(token) == 0)
		g_vars->exit_code = main_pipex(token, booleans, commands);
	else
		g_vars->exit_code = 2;
	tok_clear(token);
}
