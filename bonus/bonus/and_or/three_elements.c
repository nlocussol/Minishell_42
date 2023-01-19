/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:21:08 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 10:32:59 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_node_ok_2(t_double_list *buffer)
{
	if (buffer->next
		&& buffer->previous)
		return (1);
	return (0);
}

void	reduce_three_elements(t_double_list **temp2, t_double_list **booleans,
		int *reduction)
{
	t_double_list	*temp;
	t_double_list	*buffer;

	buffer = *temp2;
	temp = buffer->previous->previous;
	if (temp)
		temp->next = buffer;
	else
		*booleans = buffer;
	ft_double_lstdelone(buffer->previous, del);
	buffer->previous = temp;
	temp = buffer->next->next;
	if (temp)
		temp->previous = buffer;
	ft_double_lstdelone(buffer->next, del);
	buffer->next = temp;
	(*reduction)++;
}

void	three_elements(t_double_list **temp2, t_double_list **booleans,
		int *reduction)
{
	t_double_list	*buffer;

	buffer = *temp2;
	if (ft_strcmp(buffer->content, "||") == 0)
		elements_is_or(&buffer);
	else if (ft_strcmp(buffer->content, "&&") == 0)
		elements_is_and(&buffer);
	if (ft_strcmp(buffer->content, "true") == 0
		|| ft_strcmp(buffer->content, "false") == 0)
		reduce_three_elements(&buffer, booleans, reduction);
}
