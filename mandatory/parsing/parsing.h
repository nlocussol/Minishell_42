/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:25:50 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/11 10:34:18 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"

# define LEFT 1
# define RIGHT 2
# define APPEND 3
# define HERE_DOC 4
# define PIPE 5
# define CMD 6
# define FILES 7
# define LIMITER 8
# define BUILTINS 9
# define BUILTINS_F 10
# define NOT_FILE 11
# define NOT_CMD 12
# define VAR 13

int		if_quote(char *tab, int j);
int		if_convert(char *tab);
void	var_key(char *line, int *i, int *cnt);
int		find_type(char *tok);
int		pars_pipe(char **line);
void	change_env(t_tok *tok);
void	join_cmd2(t_tok *tok);
void	join_cmd(t_tok **tok);
void	type_tok(char *line, t_double_list **boolean, t_double_list **commands);
char	*put_wildcards(char *spl_cmd);
char	*convert_env(char *tab, size_t j, int j_cp);
char	*put_space(char *line);

#endif
