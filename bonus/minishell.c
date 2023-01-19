/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 23:33:46 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 15:51:08 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "bonus/and_or/and_or.h"
#include "sources/libft/libft.h"

t_vars	*g_vars;

void	init_minishell(char **env, char **str_exit)
{
	g_vars = ft_calloc(1, sizeof(t_vars));
	if (!g_vars)
		exit(1);
	g_vars->env = set_up_list(env);
	*str_exit = "exit";
	g_vars->exit_code = 0;
}

int	syntax_invalid_in_line(char **array_temp, int i)
{
	if (array_temp[i + 1] && (ft_strcmp(array_temp[i], "&&") == 0
			|| ft_strcmp(array_temp[i], "||") == 0
			|| ft_strcmp(array_temp[i], "|") == 0)
		&& (ft_strcmp(array_temp[i + 1], "&&") == 0
			|| ft_strcmp(array_temp[i + 1], "||") == 0
			|| ft_strcmp(array_temp[i + 1], "|") == 0))
		return (1);
	else if (ft_strcmp(array_temp[i], "|") == 0
		&& ((i < 0
				&& array_temp[i - 1][ft_strlen(array_temp[i - 1] - 1)] == ')')
		|| (array_temp[i + 1]
			&& array_temp[i + 1][0] == '(')))
		return (1);
	return (0);
}

int	line_valid(char *line)
{
	int		i;
	char	*line_temp;
	char	**array_temp;

	line_temp = put_space_command(line);
	array_temp = ft_split_quotes(line_temp, ' ');
	free(line_temp);
	i = 0;
	while (array_temp[i])
	{
		if (syntax_invalid_in_line(array_temp, i))
		{
			ft_fdprintf(2, "bash: syntax error near unexpected token \
`%s'\n", array_temp[i]);
			ft_free_array(array_temp);
			return (0);
		}
		i++;
	}
	ft_free_array(array_temp);
	return (1);
}

void	exec_line(char **line_read)
{
	char	*temp;

	if (*line_read && (*line_read)[0] && line_valid(*line_read))
	{
		add_history(*line_read);
		temp = ft_strtrim(*line_read, " \t");
		free(*line_read);
		signal(CTRL_C, ctrl_c_exec_start);
		if (temp && temp[0] && line_valid(temp))
			split_command(&temp, 1);
		else
			free(temp);
		signal(CTRL_C, ctrl_c_classic);
	}
	else
		free(*line_read);
}

int	main(int argc, char **argv, char **env)
{
	char	*str_exit;
	char	*prompt;
	char	*line_read;

	(void)argv;
	if (argc != 1)
		return (1);
	init_minishell(env, &str_exit);
	while (1)
	{
		g_vars->ctrl_c = 0;
		signal(CTRL_C, ctrl_c_classic);
		signal(CTRL_BACKSLASH, SIG_IGN);
		prompt = create_prompt();
		line_read = readline(prompt);
		free(prompt);
		if (!line_read)
			exit(main_exit(1, &str_exit, -1));
		complete_line_unfinished(&line_read);
		signal(CTRL_BACKSLASH, ctrl_backslash);
		exec_line(&line_read);
	}
	return (0);
}
