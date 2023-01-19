/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:26:51 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 15:27:46 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	main_pwd(int argc, char **argv, int pid)
{
	char	pwd[4097];

	(void)pid;
	(void)argv;
	(void)argc;
	getcwd(pwd, 4096);
	printf("%s\n", pwd);
	return (0);
}
