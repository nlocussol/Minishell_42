/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_display_env_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:59:22 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 16:34:40 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*supress_key(char *content)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (content[i] != '=')
		i++;
	i++;
	value = ft_calloc(ft_strlen(content) - i + 1, sizeof(char));
	j = 0;
	while (content[i + j])
	{
		value[j] = content[i + j];
		j++;
	}
	value[j] = '\0';
	return (value);
}

void	display_one_env_var(char *content)
{
	char			*key;
	char			*value;
	char			*temp;

	key = ft_strcut(content, '=');
	if (ft_strcmp(key, "_") != 0)
	{
		if (ft_strcmp(key, content) != 0)
		{
			temp = ft_strjoin(key, "=");
			free(key);
			key = temp;
			value = supress_key(content);
			ft_fdprintf(1, "declare -x %s\"%s\"\n", key, value);
			free(value);
		}
		else
			ft_fdprintf(1, "declare -x %s\n", key);
	}
	free(key);
}

void	sort_and_display_env_var(void)
{
	char			**tab;
	int				size;
	t_double_list	*new_list;
	t_double_list	*start_new_list;

	tab = set_up_tab(g_vars->env);
	size = calculate_size_tab(tab);
	sort_tab(tab, size);
	new_list = set_up_list(tab);
	start_new_list = new_list;
	while (new_list)
	{
		display_one_env_var(new_list->content);
		new_list = new_list->next;
	}
	ft_double_lstclear(&start_new_list, del);
	ft_free_array(tab);
}
