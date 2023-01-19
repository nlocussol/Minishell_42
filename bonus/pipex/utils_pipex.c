/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:30:55 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/19 15:28:52 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd_exit(int fd)
{
	if (fd == -1)
		return (1);
	return (0);
}

int	len_array(char **tab)
{
	int	cnt;

	cnt = 0;
	while (tab[cnt] != NULL)
		cnt++;
	return (cnt);
}

void	put_error(t_arg *arg, t_tok *tok, char *cmd, char *frst_cmd)
{
	DIR	*tmp;

	if (cmd && !cmd[0] && frst_cmd && !frst_cmd[0])
		return ;
	tmp = opendir(cmd);
	if (arg->path_cmd[arg->cnt] == NULL && (ft_strncmp(frst_cmd, "\"\"", 2) == 0
			|| ft_strncmp(frst_cmd, "''", 2) == 0))
		print_error(0, tok, "''", arg);
	else if (arg->path_cmd[arg->cnt] == NULL && tmp == NULL)
		print_error(0, tok, cmd, arg);
	else if (tmp != NULL)
		print_error(1, tok, cmd, arg);
	closedir(tmp);
}

char	**trim_arg(char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i] != NULL)
	{
		tmp = ft_strdup_supress_quotes(tab[i]);
		free(tab[i]);
		tab[i] = tmp;
		i++;
	}
	return (tab);
}

char	*find_trim(char *str)
{
	char	*tmp;

	if (str[0] == '\'')
		tmp = ft_strtrim(str, "'");
	else if (str[0] == '"')
		tmp = ft_strtrim(str, "\"");
	else
		tmp = ft_strdup(str);
	free(str);
	str = tmp;
	return (str);
}
