/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:23:28 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 16:13:39 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	supress_next_command(t_double_list **list_commands)
{
	t_double_list	*buffer;
	t_double_list	*next;
	int				parenthesis;

	parenthesis = 0;
	buffer = *list_commands;
	while (buffer)
	{
		next = buffer->next;
		if (ft_strcmp(buffer->content, "(") == 0)
			parenthesis++;
		else if (ft_strcmp(buffer->content, ")") == 0)
			parenthesis--;
		buffer->previous->next = buffer->next;
		buffer->next->previous = buffer->previous;
		ft_double_lstdelone(buffer, del);
		if (parenthesis == 0)
			break ;
		buffer = next;
	}
}

void	element_is_command(void **str, t_double_list **list_commands,
		t_double_list **booleans)
{
	t_double_list	*new_elt;

	*str = put_space(*str);
	if (ft_strnstr(*str, "./minishell", ft_strlen(*str)))
		signal(CTRL_C, SIG_IGN);
	type_tok(*str, list_commands, booleans);
	if (ft_strnstr(*str, "./minishell", ft_strlen(*str)))
		signal(CTRL_C, ctrl_c_classic);
	if (g_vars->exit_code == 0)
		new_elt = ft_double_lstnew(ft_strdup("true"));
	else
		new_elt = ft_double_lstnew(ft_strdup("false"));
	ft_double_lstadd_back(booleans, new_elt);
}

void	element_is_not_command(t_double_list **buffer, t_double_list **booleans)
{
	t_double_list	*new_elt;

	if (ft_strcmp((*buffer)->content, "&&") == 0)
	{
		if (ft_strcmp(ft_double_lstlast(*booleans)->content, "false") == 0)
			supress_next_command(&((*buffer)->next));
		new_elt = ft_double_lstnew(ft_strdup((*buffer)->content));
		ft_double_lstadd_back(booleans, new_elt);
	}
	else if (ft_strcmp((*buffer)->content, "||") == 0)
	{
		if (ft_strcmp(ft_double_lstlast(*booleans)->content, "true") == 0)
			supress_next_command(&((*buffer)->next));
		new_elt = ft_double_lstnew(ft_strdup((*buffer)->content));
		ft_double_lstadd_back(booleans, new_elt);
	}
	else
	{
		new_elt = ft_double_lstnew(ft_strdup((*buffer)->content));
		ft_double_lstadd_back(booleans, new_elt);
	}
}

void	element_is_parenthesis(char *str, int *parenthesis,
		t_double_list **booleans)
{
	t_double_list	*new_elt;

	new_elt = ft_double_lstnew(ft_strdup(str));
	ft_double_lstadd_back(booleans, new_elt);
	if (ft_strcmp(str, "(") == 0)
		(*parenthesis)++;
	else
		(*parenthesis)--;
}

void	launch_command(t_double_list **list_commands)
{
	int				parenthesis;
	t_double_list	*booleans;
	t_double_list	*buffer;

	parenthesis = 0;
	booleans = NULL;
	buffer = *list_commands;
	while (buffer)
	{
		if (ft_strcmp(buffer->content, "(") == 0
			|| ft_strcmp(buffer->content, ")") == 0)
			element_is_parenthesis(buffer->content, &parenthesis, &booleans);
		else if (ft_strcmp(buffer->content, "&&") != 0
			&& ft_strcmp(buffer->content, "||") != 0)
			element_is_command(&(buffer->content), list_commands, &booleans);
		else
			element_is_not_command(&buffer, &booleans);
		reduce_booleans(&booleans);
		buffer = buffer->next;
	}
	ft_double_lstclear(&booleans, del);
}
