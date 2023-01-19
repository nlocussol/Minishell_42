/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:05:49 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 18:58:40 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*wildcards(char *argument)
{
	char	*temp;
	char	**files;
	char	**delimiters;
	int		len_tab;
	int		i;

	files = create_tab_directory();
	delimiters = ft_split_quotes(argument, '*');
	i = 0;
	while (delimiters[i])
	{
		temp = trim_quotes(delimiters[i]);
		free(delimiters[i]);
		delimiters[i] = temp;
		i++;
	}
	len_tab = len_array(files);
	if (ft_strcmp(delimiters[0], "*") != 0)
		sort_files(files, delimiters, len_tab, argument);
	else
		erase_hide_file(files);
	ft_free_array(delimiters);
	return (create_new_file_char(files, len_tab));
}
