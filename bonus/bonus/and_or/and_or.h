/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:02:31 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 11:23:54 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AND_OR_H

# define AND_OR_H

void	split_command(char **command, int mode);
void	launch_command(t_double_list **list_commands);
char	**create_tab_directory(void);
void	join_command_two(t_double_list **commands);
char	*put_space_command(char *str);
void	reduce_booleans(t_double_list **booleans);
void	add_space(char **new_line, char *str, int i, int *j);
int		count_nb_to_add(char *str);
void	copy_and_skip_quotes(char **new_line, char *str, int *i, int *j);
int		check_next(t_double_list *buffer);
void	reload_split_command(char *command);

int		all_node_ok(t_double_list *buffer);
void	five_elements(t_double_list **temp2, t_double_list **booleans,
			int *reduction);
void	elements_is_and(t_double_list **temp);
void	elements_is_or(t_double_list **temp);
int		all_node_ok_2(t_double_list *buffer);
void	three_elements(t_double_list **temp2, t_double_list **booleans,
			int *reduction);
void	reduce_three_elements(t_double_list **temp2, t_double_list **booleans,
			int *reduction);

#endif
