/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:27:57 by averdon           #+#    #+#             */
/*   Updated: 2023/01/19 13:29:17 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H

# define CD_H

int		main_cd(int argc, char **argv, int pid);
int		return_home(int pid);
void	return_root(char **pwd, int pid);
int		go_to_path(char **argv, char **pwd, int pid, int at_root);
int		home_set(void);
void	update_pwd(char *new_path, int pid);
void	update_old_pwd(char *pwd, int pid);

#endif
