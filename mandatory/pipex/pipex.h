/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:21:31 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/17 15:43:36 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../minishell.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_arg
{
	int		bin_pipe;
	int		path;
	int		not_file;
	char	**path_cmd;
	int		cnt;
	int		*pid;
	char	**path_env;
	char	**env;
	int		*fd;
	int		exit;
	int		pipe[2][2];
	int		here_pipe[2];
	int		here_doc;
}			t_arg;

int		right_fd(t_tok *buf, t_arg *arg);
int		left_fd(t_tok *buf, t_arg *arg);
void	exit_env_var(t_arg *arg, t_tok *cmd, char *first_cmd, int cnt);
void	tok_clear(t_tok *tok);
void	void_fork(t_arg *arg, t_tok *tok, t_double_list **boolean,
			t_double_list **commands);
int		access_cmd(t_arg *arg, t_tok *cmd, char *first_cmd);
void	check_type(t_tok **tok, t_arg *arg);
void	file_dup2(t_arg *arg);
int		fd_exit(int fd);
int		if_pipe(t_tok *token);
int		if_right(t_tok *token);
void	file_dup2(t_arg *arg);
char	**trim_arg(char **tab);
int		check_files_in(int fd, char *filename, t_tok *tok, t_arg *arg);
int		check_files_out(int fd, char *filename, t_tok *tok, t_arg *arg);
int		total_cmd(t_tok *token);
void	do_dup2(t_tok *token, t_arg *arg);
int		len_array(char **tab);
void	right_dup2(t_arg *arg);
void	left_dup2(t_arg *arg);
void	other_dup2(t_arg *arg);
char	*find_trim(char *str);
void	check_free(void *ptr);
void	free_split(char	**str);
int		check_builtins(char *cmd, t_arg *arg);
void	check_limiter(char *line, t_arg *arg, t_tok *token);
int		main_pipex(t_tok *token, t_double_list **boolean,
			t_double_list **commands);
void	put_error(t_arg *arg, t_tok *cmd, char *first_cmd, char *frst_cmd);
void	exe_cmd(t_arg *arg, t_tok *token, t_double_list **boolean,
			t_double_list **commands);
void	here_doc(t_arg *arg, t_tok *token);
void	ft_free_arg(t_arg *arg);
void	wait_pid(t_arg *arg, t_tok *token);
void	ft_close(t_arg *arg);
void	check_fd(int fd);
void	initialized_pipe(t_arg *arg, t_tok *token);
void	split_path(t_arg *arg, char **envp);
void	ft_free(t_arg *arg);
void	fill_cmd(t_arg *arg);
void	initialized_f(t_arg	*arg, t_tok *token);
void	print_error(int error_type, t_tok *token, char *cmd, t_arg *arg);
void	access_file(t_arg *files);
int		check_sign(t_tok *token, t_arg *arg, char *line, int fd);
void	child_program(t_arg *arg, t_tok *token,
			t_double_list **boolean, t_double_list **commands);
void	child_builtins(t_arg *arg, t_tok **token,
			t_double_list **boolean, t_double_list **commands);

#endif
