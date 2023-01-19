/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_unfinished.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:07:55 by averdon           #+#    #+#             */
/*   Updated: 2023/01/13 14:51:41 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_closed(char *line)
{
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '|')
		return (1);
	else
		return (0);
}

int	line_unfinished(char **line, int mode)
{
	if (!(*line))
		return (-1);
	if (quotes_closed(*line))
		return (quotes_closed(*line));
	else if (links_command_closed(*line, 0))
	{
		if (mode)
			return (links_command_closed(*line, 1));
		else
			return (links_command_closed(*line, 0));
	}
	else if (pipe_closed(*line))
		return (pipe_closed(*line));
	else if (paranthesis_closed(*line, 0))
	{
		if (mode)
			return (paranthesis_closed(*line, 1));
		else
			return (paranthesis_closed(*line, 0));
	}
	else
		return (0);
}

void	add_new_elt_line(char **line)
{
	char	*str;
	char	*temp;

	str = readline("> ");
	if (!str)
		ft_fdprintf(2, "bash: syntax error unexpected end of file\n");
	if (!str || g_vars->ctrl_c == 1)
	{
		free(*line);
		*line = NULL;
		return ;
	}
	temp = ft_strtrim(str, " ");
	free(str);
	str = ft_strjoin(*line, temp);
	free(*line);
	*line = put_space_parsing(str);
	free(temp);
}

void	complete_line_unfinished(char **line)
{
	int		fd;
	int		line_unfinished_start;

	line_unfinished_start = 0;
	if (line_unfinished(line, 0))
		fd = dup(0);
	if (line_unfinished(line, 0))
		line_unfinished_start = 1;
	signal(CTRL_C, ctrl_c_exec_and_heredoc);
	*line = put_space_parsing(*line);
	while (line_unfinished(line, 0) > 0)
		add_new_elt_line(line);
	if (*line && line_unfinished(line, 1) < 0)
	{
		free(*line);
		*line = NULL;
	}
	if (line_unfinished_start)
	{
		dup2(fd, 0);
		close(fd);
	}
	signal(CTRL_C, ctrl_c_classic);
}
