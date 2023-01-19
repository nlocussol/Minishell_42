/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:56:21 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 19:16:50 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	*set_up_char_passed(int len_tab)
{
	int		*char_passed;
	int		i;

	char_passed = ft_calloc(len_tab, sizeof(int));
	if (!char_passed)
		return (NULL);
	i = 0;
	while (i < len_tab)
	{
		char_passed[i] = 0;
		i++;
	}
	return (char_passed);
}

void	check_one_file(int *char_passed, char **file, char *delimiter)
{
	char	*actual_file;

	if (*char_passed <= (int)ft_strlen(*file))
	{
		actual_file = ft_strnstr(&((*file)[*char_passed]),
				delimiter, ft_strlen(&((*file)[*char_passed])));
		if (!actual_file)
		{
			free(*file);
			*file = NULL;
		}
		else
			*char_passed = ft_strlen(*file)
				- ft_strlen(actual_file) + ft_strlen(delimiter);
	}
	else
	{
		free(*file);
		*file = NULL;
	}
}

void	start_and_end_of_file(char *argument, char **file)
{
	int		len_filename;

	if (argument[0] != '*')
	{
		if (*file && (*file)[0] != argument[0])
		{
			free(*file);
			*file = NULL;
		}
	}
	if (argument[ft_strlen(argument) - 1] != '*')
	{
		len_filename = ft_strlen(*file) - 1;
		if (*file && (*file)[len_filename] != argument[ft_strlen(argument) - 1])
		{
			free(*file);
			*file = NULL;
		}
	}
}

void	sort_files(char **files, char **delimiters, int len_tab, char *argument)
{
	int		i;
	int		y;
	int		*char_passed;

	i = 0;
	char_passed = set_up_char_passed(len_tab);
	while (delimiters[i])
	{
		y = -1;
		while (++y < len_tab)
			check_one_file(&char_passed[y], &files[y], delimiters[i]);
		i++;
	}
	y = -1;
	while (++y < len_tab)
		start_and_end_of_file(argument, &files[y]);
	free(char_passed);
}

void	erase_hide_file(char **files)
{
	int	i;

	i = 0;
	while (files[i])
	{
		if (files[i][0] == '.')
		{
			free(files[i]);
			files[i] = NULL;
		}
		i++;
	}
}
