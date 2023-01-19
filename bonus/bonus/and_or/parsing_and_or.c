/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:35:57 by averdon           #+#    #+#             */
/*   Updated: 2023/01/16 14:02:52 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*put_space_command(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_line;

	len = ft_strlen(str);
	new_line = ft_calloc(len + 1 + count_nb_to_add(str), sizeof(char));
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
			copy_and_skip_quotes(&new_line, str, &i, &j);
		add_space(&new_line, str, i, &j);
		i++;
		j++;
	}
	return (new_line);
}

void	join_command_two(t_double_list **commands)
{
	char			*temp;
	t_double_list	*next;
	t_double_list	*buffer;

	buffer = *commands;
	while (buffer->next)
	{
		next = buffer->next;
		if (check_next(buffer))
		{
			temp = ft_strjoin(" ", buffer->next->content);
			free(buffer->next->content);
			buffer->next->content = ft_strjoin(buffer->content, temp);
			free(temp);
			if (buffer->previous)
				buffer->previous->next = buffer->next;
			else
				*commands = buffer->next;
			buffer->next->previous = buffer->previous;
			ft_double_lstdelone(buffer, del);
		}
		buffer = next;
	}
}

void	display_command(t_double_list **list_commands, int mode)
{
	char					*command;
	t_double_list			*new_elt;
	t_double_list			*buffer;
	static t_double_list	*new_list_commands;

	buffer = *list_commands;
	while (buffer)
	{
		command = buffer->content;
		if (command[0] == '(' && command[ft_strlen(command) - 1] == ')'
			&& ft_strlen(command) > 3)
			reload_split_command(command);
		else
		{
			new_elt = ft_double_lstnew(ft_strdup(command));
			ft_double_lstadd_back(&new_list_commands, new_elt);
		}	
		buffer = buffer->next;
	}
	ft_double_lstclear(list_commands, del);
	if (mode)
	{
		launch_command(&new_list_commands);
		ft_double_lstclear(&new_list_commands, del);
	}
}

void	trim_first_parenthesis(char **command)
{
	char			*command_trimmed;

	command_trimmed = ft_strdup(&((*command)[1]));
	command_trimmed[ft_strlen(command_trimmed) - 1] = '\0';
	if (parenthesis_closed_split(command_trimmed))
	{
		free(*command);
		*command = ft_strdup(command_trimmed);
	}
	free(command_trimmed);
}

void	split_command(char **command, int mode)
{
	char			*temp;
	char			**tab_commands;
	t_double_list	*new_elt;
	t_double_list	*list_commands;

	temp = ft_strtrim(*command, " ");
	free(*command);
	*command = temp;
	if ((*command)[0] == '(' && (*command)[ft_strlen(*command) - 1] == ')')
		trim_first_parenthesis(command);
	temp = put_space_command(*command);
	free(*command);
	*command = temp;
	tab_commands = ft_split_quotes_parenthesis(*command, ' ');
	free(*command);
	list_commands = set_up_list(tab_commands);
	ft_free_array(tab_commands);
	join_command_two(&list_commands);
	new_elt = ft_double_lstnew(ft_strdup("("));
	ft_double_lstadd_front(&list_commands, new_elt);
	new_elt = ft_double_lstnew(ft_strdup(")"));
	ft_double_lstadd_back(&list_commands, new_elt);
	display_command(&list_commands, mode);
}
