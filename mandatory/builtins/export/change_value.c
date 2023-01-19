/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:57:38 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 13:32:37 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_value(char **temp, char *arg, int pid)
{
	t_double_list	*new_elt;
	char			*tab[2];

	tab[0] = "unset";
	tab[1] = *temp;
	main_unset(2, tab, pid);
	new_elt = ft_double_lstnew(ft_strdup(arg));
	ft_double_lstadd_back(&g_vars->env, new_elt);
}
