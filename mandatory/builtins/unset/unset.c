/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:26:56 by averdon           #+#    #+#             */
/*   Updated: 2023/01/19 13:55:50 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_node(void)
{
	if (g_vars->env->previous)
		g_vars->env->previous->next = g_vars->env->next;
	if (g_vars->env->next)
		g_vars->env->next->previous = g_vars->env->previous;
	ft_double_lstdelone(g_vars->env, del);
}

void	compare(int *node_deleted, char *arg)
{
	char			*temp;

	temp = ft_strcut(g_vars->env->content, '=');
	if (ft_strcmp(temp, arg) == 0)
	{
		del_node();
		free(temp);
		*node_deleted = 1;
		return ;
	}
	free(temp);
}

void	arg_is_valid(char *arg)
{
	int				node_deleted;
	t_double_list	*buffer;

	buffer = g_vars->env;
	node_deleted = 0;
	while (g_vars->env)
	{
		compare(&node_deleted, arg);
		if (node_deleted)
			break ;
		g_vars->env = g_vars->env->next;
	}
	g_vars->env = buffer;
}

int	main_unset(int argc, char **argv, int pid)
{
	int				i;
	int				return_value;

	(void)pid;
	return_value = 0;
	if (argc <= 1)
		return (return_value);
	i = 1;
	while (i < argc)
	{
		if (arg_valid(argv[i]))
			arg_is_valid(argv[i]);
		else
		{
			ft_fdprintf(2, "bash: unset: `%s`: \
not a valid identifier\n", argv[i]);
			return_value = 1;
		}
		i++;
	}
	return (return_value);
}
