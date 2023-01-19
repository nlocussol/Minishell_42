/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:27:51 by averdon           #+#    #+#             */
/*   Updated: 2022/12/13 14:11:21 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H

# define ECHO_H

char	*ft_strdup_supress_quotes(const char *s);
int		main_echo(int argc, char **argv, int pid);
void	parsing_echo(int argc, char **argv);

#endif
