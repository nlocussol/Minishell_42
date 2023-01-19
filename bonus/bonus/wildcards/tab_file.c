/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:43:57 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 19:06:03 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

char	**complete_tab(char **tab_1, char **tab_new_elements)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	while (tab_1[i])
		i++;
	j = 0;
	while (tab_new_elements[j])
		j++;
	new_tab = ft_calloc(i + j + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (tab_1[++i])
		new_tab[i] = ft_strdup(tab_1[i]);
	j = -1;
	while (tab_new_elements[++j])
		new_tab[i + j] = ft_strdup(tab_new_elements[j]);
	new_tab[i + j] = NULL;
	free_tab(tab_1);
	free_tab(tab_new_elements);
	return (new_tab);
}

char	**ft_join_tab(char **tab_1, char *new_elements)
{
	char	**new_tab;
	char	**tab_new_elements;

	tab_new_elements = ft_split(new_elements, ' ');
	if (!tab_new_elements || !tab_new_elements[0])
	{
		free_tab(tab_new_elements);
		return (NULL);
	}
	if (!tab_1)
		return (tab_new_elements);
	new_tab = complete_tab(tab_1, tab_new_elements);
	return (new_tab);
}

char	**create_tab_directory(void)
{
	DIR				*directory;
	struct dirent	*new_file;
	char			**files;

	directory = opendir(".");
	files = NULL;
	if (directory)
	{
		new_file = readdir(directory);
		while (new_file)
		{
			if (ft_strcmp(new_file->d_name, ".") != 0
				&& ft_strcmp(new_file->d_name, "..") != 0)
				files = ft_join_tab(files, new_file->d_name);
			new_file = readdir(directory);
		}
		closedir(directory);
	}
	return (files);
}
