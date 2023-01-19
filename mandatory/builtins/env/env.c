/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:26:31 by averdon           #+#    #+#             */
/*   Updated: 2023/01/17 15:25:53 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	main_env(int argc, char **argv, int pid)
{
	int				i;
	t_double_list	*buffer;

	(void)pid;
	(void)argv;
	if (argc != 1)
	{
		ft_fdprintf(2, "no option allowed\n");
		return (1);
	}
	i = 0;
	buffer = g_vars->env;
	while (buffer)
	{
		if (ft_strchr(buffer->content, '='))
			printf("%s\n", (char *)buffer->content);
		buffer = buffer->next;
	}
	return (0);
}
