/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:15:20 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 15:51:36 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_prompt_next(char *prompt)
{
	char			pwd[4097];
	char			*temp;

	getcwd(pwd, 4096);
	temp = ft_strjoin(prompt, pwd);
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, "$ ");
	free(prompt);
	prompt = temp;
	return (prompt);
}

char	*create_prompt(void)
{
	char			*prompt;
	char			*temp;
	char			*new_block;

	prompt = value_of_key("USER");
	temp = ft_strjoin(prompt, "@");
	free(prompt);
	prompt = temp;
	new_block = value_of_key("SESSION_MANAGER");
	temp = ft_strtrim_start(new_block, "local/");
	free(new_block);
	new_block = temp;
	temp = ft_strjoin(prompt, new_block);
	free(prompt);
	free(new_block);
	prompt = temp;
	temp = ft_strcut(prompt, '.');
	free(prompt);
	prompt = temp;
	temp = ft_strjoin(prompt, ":~");
	free(prompt);
	prompt = temp;
	return (create_prompt_next(prompt));
}
