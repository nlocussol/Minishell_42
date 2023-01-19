/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 23:33:46 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 15:34:50 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exec_line(char **line_read)
{
	char	*temp;

	if (*line_read && (*line_read)[0])
	{
		add_history(*line_read);
		temp = ft_strtrim(*line_read, " \t");
		signal(CTRL_C, ctrl_c_exec_start);
		free(*line_read);
		*line_read = put_space(temp);
		if (!quotes_closed(*line_read))
		{
			if ((*line_read)[0])
				type_tok(*line_read, NULL, NULL);
			else
				free(*line_read);
		}
		else
		{
			ft_fdprintf(2, "a quote isn't closed\n");
			free(*line_read);
		}
		signal(CTRL_C, ctrl_c_classic);
	}
	else
		free(*line_read);
}

int	main(int argc, char **argv, char **env)
{
	char	*str_exit;
	char	*line_read;
	char	*prompt;

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
		signal(CTRL_BACKSLASH, ctrl_backslash);
		exec_line(&line_read);
	}
	return (0);
}
