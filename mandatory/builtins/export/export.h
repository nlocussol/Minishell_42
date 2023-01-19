/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:27:36 by averdon           #+#    #+#             */
/*   Updated: 2022/12/09 19:00:55 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H

# define EXPORT_H

int		main_export(int argc, char **new_variable, int pid);
char	**set_up_tab(t_double_list *list);
void	change_value(char **temp, char *arg, int pid);
void	append_value(char *arg, int pid);
void	sort_and_display_env_var(void);
int		calculate_size_tab(char **tab);
void	sort_tab(char **tab, int size);
int		arg_valid(char *arg);
#endif
