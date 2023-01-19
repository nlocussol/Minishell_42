/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:42:23 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/10 16:07:00 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strtok(char *str, char charset)
{
	static int	i = -1;
	static char	*str_saved;
	char		**array;
	char		*str_return;

	i++;
	if (str)
	{
		str_saved = str;
		i = 0;
	}
	array = ft_split_quotes(str_saved, charset);
	if (i >= len_array(array))
	{
		free_split(array);
		return (NULL);
	}
	else
	{
		str_return = ft_strdup(array[i]);
		free_split(array);
		return (str_return);
	}
}
