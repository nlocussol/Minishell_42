/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 23:34:07 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 15:51:46 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del(void *content)
{
	free(content);
	content = NULL;
}

void	del_tok(char *token)
{
	free(token);
	token = NULL;
}

void	free_global(void)
{
	ft_double_lstclear(&g_vars->env, del);
	free(g_vars);
}

t_double_list	*set_up_list(char **env)
{
	int				i;
	t_double_list	*env_list;
	t_double_list	*new_elt;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		new_elt = ft_double_lstnew(ft_strdup(env[i]));
		ft_double_lstadd_back(&env_list, new_elt);
		i++;
	}
	return (env_list);
}

char	find_limiter(char *str)
{
	int		i;
	char	limiter;

	i = 0;
	limiter = '\0';
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (str[i] == '\"' && limiter == '\"')
				limiter = '\0';
			else if (str[i] == '\'' && limiter == '\'')
				limiter = '\0';
			else if (limiter == '\0')
				limiter = str[i];
		}
		i++;
	}
	return (limiter);
}
