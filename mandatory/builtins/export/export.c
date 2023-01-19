/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:26:46 by averdon           #+#    #+#             */
/*   Updated: 2023/01/13 15:21:45 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*parse_value(char *value)
{
	if (value[0] == '\"' && value[ft_strlen(value) - 1] == '\"')
		value = ft_strtrim(value, "\"");
	else if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		value = ft_strtrim(value, "\'");
	else
		value = ft_strdup(value);
	return (value);
}

void	value_exist(char **arg, char **value, char **temp)
{
	char			*temp2;

	*value = &((*value)[1]);
	*value = parse_value(*value);
	free(*arg);
	*arg = ft_strdup(*temp);
	temp2 = ft_strjoin(*arg, "=");
	free(*arg);
	*arg = ft_strjoin(temp2, *value);
	free(temp2);
}

void	modify_env_var(char **arg, int pid)
{
	char			*temp;
	char			*temp2;
	char			*value;

	temp = ft_strcut(*arg, '=');
	value = ft_strchr(*arg, '=');
	if (value)
		value_exist(arg, &value, &temp);
	temp2 = value_of_key(*arg);
	if (!(!value && temp2[0]))
	{
		if (temp[ft_strlen(temp) - 1] == '+')
			append_value(*arg, pid);
		else
			change_value(&temp, *arg, pid);
	}
	free(temp2);
	free(temp);
	free(value);
}

int	main_export(int argc, char **argv, int pid)
{
	int	i;
	int	return_value;

	return_value = 0;
	if (argc == 1)
		sort_and_display_env_var();
	else
	{
		i = 1;
		while (i < argc)
		{
			if (arg_valid(argv[i]))
				modify_env_var(&argv[i], pid);
			else
			{
				ft_fdprintf(2, "bash: export: `%s`: \
not a valid identifier\n", argv[i]);
				return_value = 1;
			}
			i++;
		}
	}
	return (return_value);
}
