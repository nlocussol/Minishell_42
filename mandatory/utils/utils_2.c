/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:16:06 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 15:18:06 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_quotes(char *str)
{
	char	*temp;

	if (str[0] == '\'')
		temp = ft_strtrim(str, "\'");
	else if (str[0] == '\"')
		temp = ft_strtrim(str, "\"");
	else
		temp = ft_strdup(str);
	return (temp);
}
