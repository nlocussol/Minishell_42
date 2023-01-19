/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:57:31 by averdon           #+#    #+#             */
/*   Updated: 2023/01/11 16:58:29 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_env_var_value(char *temp)
{
	char			*value;
	t_double_list	*buffer;

	value = NULL;
	buffer = g_vars->env;
	while (buffer)
	{
		if (ft_strncmp(buffer->content, temp, ft_strlen(temp)) == 0)
			value = ft_strchr(buffer->content, '=');
		buffer = buffer->next;
	}
	return (value);
}

void	erase_old_value(char **env_var, char **new_value, char *arg, int pid)
{
	char			*tab[2];
	char			*actual_value;
	char			*value_to_add;

	*env_var = ft_strcut(arg, '+');
	actual_value = find_env_var_value(*env_var);
	value_to_add = ft_strchr(arg, '=');
	value_to_add = &value_to_add[1];
	if (actual_value)
		*new_value = ft_strjoin(actual_value, value_to_add);
	else
		*new_value = ft_strjoin("=", value_to_add);
	tab[0] = "unset";
	tab[1] = *env_var;
	main_unset(2, tab, pid);
}

void	append_value(char *arg, int pid)
{
	char			*env_var;
	char			*new_value;
	char			*temp;
	t_double_list	*new_elt;

	erase_old_value(&env_var, &new_value, arg, pid);
	temp = ft_strjoin(env_var, new_value);
	free(env_var);
	free(new_value);
	env_var = temp;
	new_elt = ft_double_lstnew(ft_strdup(temp));
	ft_double_lstadd_back(&g_vars->env, new_elt);
	free(temp);
}
