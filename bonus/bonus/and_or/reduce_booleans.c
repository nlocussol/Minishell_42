/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_booleans.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:12:31 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 10:52:05 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_to_reduce(t_double_list **temp, t_double_list **booleans,
		int *reduction)
{
	t_double_list	*buffer;

	buffer = *temp;
	if (ft_strcmp(buffer->content, "||") == 0
		|| ft_strcmp(buffer->content, "&&") == 0)
	{
		if (all_node_ok(buffer))
			five_elements(&buffer, booleans, reduction);
		else if (all_node_ok_2(buffer))
			three_elements(&buffer, booleans, reduction);
	}
	else if (ft_strcmp(buffer->content, "true") == 0
		|| ft_strcmp(buffer->content, "false") == 0)
	{
		if (all_node_ok_2(buffer)
			&& ft_strcmp(buffer->previous->content, "(") == 0
			&& ft_strcmp(buffer->next->content, ")") == 0)
			reduce_three_elements(&buffer, booleans, reduction);
	}
}

void	reduce_booleans(t_double_list **booleans)
{
	int				reduction;
	int				round;
	t_double_list	*buffer;

	reduction = 1;
	round = 0;
	while (reduction != 0)
	{
		reduction = 0;
		round++;
		buffer = *booleans;
		while (buffer)
		{
			check_to_reduce(&buffer, booleans, &reduction);
			buffer = buffer->next;
		}
	}
}
