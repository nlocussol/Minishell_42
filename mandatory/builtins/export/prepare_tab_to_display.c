/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_tab_to_display.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:04:36 by averdon           #+#    #+#             */
/*   Updated: 2022/11/30 18:06:03 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	list_sorted(t_double_list **head)
{
	t_double_list	*temp;
	int				content_one;
	int				content_two;

	temp = *head;
	content_one = 0;
	content_two = 0;
	while (temp && temp->next)
	{
		if (ft_strcmp(temp->content, temp->next->content) > 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

char	**set_up_tab(t_double_list *list)
{
	int		size_list;
	int		i;
	char	**tab;

	size_list = ft_double_lstsize(list);
	tab = ft_calloc(size_list + 1, sizeof(char *));
	i = 0;
	while (list)
	{
		tab[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	sort_tab(char **tab, int size)
{
	int		count;
	int		count2;
	char	*temp;

	count = 0;
	temp = NULL;
	while (count < size)
	{
		count2 = 1;
		while (count2 < size - 1)
		{
			if (ft_strcmp(tab[count2], tab[count2 + 1]) > 0)
			{
				temp = tab[count2];
				tab[count2] = tab[count2 + 1];
				tab[count2 + 1] = temp;
			}
			count2++;
		}
		count++;
	}
}

int	calculate_size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
