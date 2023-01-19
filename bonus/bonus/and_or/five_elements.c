/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   five_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:02:58 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 10:20:51 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_node_ok(t_double_list *buffer)
{
	if (buffer->next && buffer->next->next
		&& buffer->previous && buffer->previous->previous)
		return (1);
	return (0);
}

void	elements_is_or(t_double_list **temp)
{
	t_double_list	*buffer;

	buffer = *temp;
	if (ft_strcmp(buffer->previous->content, "true") == 0
		|| ft_strcmp(buffer->next->content, "true") == 0)
	{
		free(buffer->content);
		buffer->content = ft_strdup("true");
	}
	else if (ft_strcmp(buffer->previous->content, "false") == 0
		&& ft_strcmp(buffer->next->content, "false") == 0)
	{
		free(buffer->content);
		buffer->content = ft_strdup("false");
	}
}

void	elements_is_and(t_double_list **temp)
{
	t_double_list	*buffer;

	buffer = *temp;
	if (ft_strcmp(buffer->previous->content, "true") == 0
		&& ft_strcmp(buffer->next->content, "true") == 0)
	{
		free(buffer->content);
		buffer->content = ft_strdup("true");
	}
	else if (ft_strcmp(buffer->previous->content, "false") == 0
		|| ft_strcmp(buffer->next->content, "false") == 0)
	{
		free(buffer->content);
		buffer->content = ft_strdup("false");
	}
}

void	reduce_five_elements(t_double_list **temp2, t_double_list **booleans,
		int *reduction)
{
	t_double_list	*temp;
	t_double_list	*buffer;

	buffer = *temp2;
	temp = buffer->previous->previous->previous;
	if (temp)
		temp->next = buffer;
	else
		*booleans = buffer;
	ft_double_lstdelone(buffer->previous->previous, del);
	ft_double_lstdelone(buffer->previous, del);
	buffer->previous = temp;
	temp = buffer->next->next->next;
	if (temp)
		temp->previous = buffer;
	ft_double_lstdelone(buffer->next->next, del);
	ft_double_lstdelone(buffer->next, del);
	buffer->next = temp;
	(*reduction)++;
}

void	five_elements(t_double_list **temp2, t_double_list **booleans,
		int *reduction)
{
	t_double_list	*buffer;

	buffer = *temp2;
	if (ft_strcmp(buffer->previous->content, "(") != 0
		&& ft_strcmp(buffer->previous->content, ")") != 0
		&& ft_strcmp(buffer->next->content, "(") != 0
		&& ft_strcmp(buffer->next->content, ")") != 0)
	{
		if (ft_strcmp(buffer->content, "||") == 0)
			elements_is_or(&buffer);
		else if (ft_strcmp(buffer->content, "&&") == 0)
			elements_is_and(&buffer);
		if (ft_strcmp(buffer->content, "true") == 0
			|| ft_strcmp(buffer->content, "false") == 0)
			reduce_five_elements(&buffer, booleans, reduction);
	}
}
