/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:26:24 by averdon           #+#    #+#             */
/*   Updated: 2023/01/17 15:19:27 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	one_argument(char **argv, char **str)
{
	char	*temp;

	if (ft_strncmp(argv[1], "-n", ft_strlen(argv[1])) == 0)
		*str = ft_strdup("");
	else
	{
		*str = ft_strdup_supress_quotes(argv[1]);
		temp = ft_strjoin(*str, "\n");
		free(*str);
		*str = temp;
	}
}

void	expand_string(char **argv, int i, char **str)
{
	char	*temp;
	char	*temp2;

	if (argv[i][0])
	{
		if (*str && (*str)[0])
		{
			temp = ft_strjoin(*str, " ");
			free(*str);
			temp2 = ft_strdup_supress_quotes(argv[i]);
			*str = ft_strjoin(temp, temp2);
			free(temp);
			free(temp2);
		}
		else
		{
			if (*str)
				free(*str);
			*str = ft_strdup_supress_quotes(argv[i]);
		}
	}
	else if (!(*str))
			*str = ft_strdup("");
}

void	two_or_more_arguments(int argc, char **argv, char **str)
{
	int		i;
	char	*temp;

	i = 1;
	if (ft_strcmp(argv[1], "-n") == 0)
		i++;
	while (i < argc)
	{
		expand_string(argv, i, str);
		i++;
	}
	if (ft_strcmp(argv[1], "-n") != 0)
	{
		temp = ft_strjoin(*str, "\n");
		free(*str);
		*str = temp;
	}
}

int	main_echo(int argc, char **argv, int pid)
{
	char	*str;

	(void)pid;
	str = NULL;
	parsing_echo(argc, argv);
	if (argc == 1)
		str = ft_strdup("\n");
	else if (argc == 2)
		one_argument(argv, &str);
	else
		two_or_more_arguments(argc, argv, &str);
	printf("%s", str);
	free(str);
	return (0);
}
