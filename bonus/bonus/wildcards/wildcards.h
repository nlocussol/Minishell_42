/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:58:57 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 19:01:55 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H

# define WILDCARDS_H

char	*create_new_file_char(char **files, int len_tab);
void	erase_hide_file(char **files);
void	sort_files(char **files, char **delimiters,
			int len_tab, char *argument);
char	*wildcards(char *argument);
char	**ft_join_tab(char **tab_1, char *new_elements);

#endif
