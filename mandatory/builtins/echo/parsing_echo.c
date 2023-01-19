/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:49:06 by averdon           #+#    #+#             */
/*   Updated: 2023/01/19 15:34:39 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_arg(char **argv, int y, int i, int memory)
{
	if (y == 1)
		memory = 1;
	if (!memory)
	{
		free(argv[i]);
		argv[i] = ft_strdup("");
	}
}

void	supress_others_arg(char **argv)
{
	int		i;
	int		y;
	int		memory;
	char	*temp;

	i = 1;
	memory = 0;
	while (argv[++i] && !memory)
	{
		y = 0;
		memory = 0;
		temp = trim_quotes(argv[i]);
		if (temp[0] != '-')
			memory = 1;
		while (temp[0] && temp[++y] && !memory)
		{
			if (temp[y] != 'n')
				memory = 1;
		}
		change_arg(argv, y, i, memory);
		free(temp);
	}
}

void	modify_first_arg(char **argv)
{
	int		i;
	int		memory;
	char	*temp;

	i = 1;
	memory = 0;
	temp = trim_quotes(argv[1]);
	if (temp[0] != '-')
		memory = 1;
	while (temp[0] && temp[i] && !memory)
	{
		if (temp[i] != 'n')
			memory = 1;
		i++;
	}
	if (i == 1)
		memory = 1;
	free(temp);
	if (!memory)
	{
		free(argv[1]);
		argv[1] = ft_strdup("-n");
		supress_others_arg(argv);
	}
}

void	parsing_echo(int argc, char **argv)
{
	if (argc == 1)
		return ;
	else
		modify_first_arg(argv);
}
