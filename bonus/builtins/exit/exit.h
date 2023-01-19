/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:27:41 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 13:47:07 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H

# define EXIT_H

int		main_exit(int argc, char **argv, int pid);
int		will_quit(int argc, char **argv);
char	*parse_arg(char *arg);

#endif
