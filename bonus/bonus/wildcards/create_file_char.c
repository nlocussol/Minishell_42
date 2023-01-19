/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:56:54 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 18:58:04 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	calculate_nb_files(char **files, int len_tab)
{
	int	y;
	int	nb_files;

	y = 0;
	nb_files = 0;
	while (y < len_tab)
	{
		if (files[y])
			nb_files++;
		y++;
	}
	return (nb_files);
}

void	free_split_modify(char **array, int len_tab)
{
	int	i;

	i = 0;
	while (i < len_tab)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

char	*create_new_file_char(char **files, int len_tab)
{
	int		y;
	int		nb_files;
	char	*files_to_return;
	char	*temp;

	nb_files = calculate_nb_files(files, len_tab);
	y = -1;
	files_to_return = NULL;
	while (++y < len_tab)
	{
		if (files[y])
		{
			if (!files_to_return)
				files_to_return = ft_strdup(files[y]);
			else
			{
				temp = ft_strjoin(files_to_return, " ");
				free(files_to_return);
				files_to_return = ft_strjoin(temp, files[y]);
				free(temp);
			}
		}
	}
	free_split_modify(files, len_tab);
	return (files_to_return);
}
