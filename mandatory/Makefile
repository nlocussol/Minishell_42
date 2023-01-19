# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 17:13:34 by nlocusso          #+#    #+#              #
#    Updated: 2023/01/19 13:38:04 by averdon          ###   ########.fr        #
#    Updated: 2023/01/10 15:15:05 by nlocusso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		?= minishell.c \
			  utils/utils.c \
			  utils/utils_2.c \
			  utils/prompt.c \
			  utils/signals_handler.c \
			  utils/value_of_key.c \
			  utils/parse_line_quotes.c \
			  parsing/put_space.c \
			  parsing/var_env.c \
			  parsing/utils_env.c \
			  parsing/token.c \
			  parsing/join_token.c \
			  builtins/cd/cd.c \
			  builtins/cd/return_home.c \
			  builtins/echo/echo.c \
			  builtins/echo/parsing_echo.c \
			  builtins/env/env.c \
			  builtins/exit/exit.c \
			  builtins/exit/parse.c \
			  builtins/export/export.c \
			  builtins/export/parsing_export.c \
			  builtins/export/append_value.c \
			  builtins/export/change_value.c \
			  builtins/export/prepare_tab_to_display.c \
			  builtins/export/sort_and_display_env_var.c \
			  builtins/pwd/pwd.c \
			  builtins/unset/unset.c \
			  builtins/main_builtins.c \
			  pipex/exe_cmd.c \
			  pipex/exe_builtins.c \
			  pipex/free.c \
			  pipex/check_files.c \
			  pipex/utils_pipex.c \
			  pipex/initialized.c \
			  pipex/main_pipex.c \
			  pipex/pars_arg.c \
			  pipex/pars_exec.c \
			  pipex/dup2.c \
			  pipex/utils_dup2.c \
			  pipex/check.c \

OBJS		?= ${SRCS:.c=.o}

NAME		?= minishell

COMPILER	?= clang

RM			?= @rm -f

CFLAGS		?= -Wall -Wextra -Werror -g 

LIBRARY     ?= -Lsources/libft -lft \
			   -Lsources/libft/ft_fdprintf -lftfdprintf \
			   -lreadline

all :        ${NAME}

.c.o :		${OBJS}
			@(${COMPILER} ${CFLAGS} -c $< -o ${<:.c=.o} || (clear; printf "\033[0;31;1mcompilation failed\n\033[0m"; ${COMPILER} ${CFLAGS} -c $< -o ${<:.c=.o} ; exit 1))
	
${NAME}:	${OBJS}
			@clear
			@printf "\033[93;1;5mCompiling ...\n\033[0m"
			@make -C sources/libft
			@${COMPILER} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBRARY}
			@clear
			@printf '\033[0;92;1mCompilation finished\n\033[0m'

clear:
			@clear

compiling:
			@printf "\033[93;1;5mCompiling ...\n\033[0m"

cleaning:
			@printf "\033[93;1;5mCleaning ...\n\033[0m"

clean :		clear cleaning
			${RM} ${OBJS} 
			@make -C sources/libft clean
			@clear
			@printf '\033[0;92;1mCleaning finished\n\033[0m'

fclean :	clear clean cleaning 
			${RM} ${NAME} 
			@make -C sources/libft fclean
			@clear
			@printf '\033[0;92;1mCleaning finished\n\033[0m'

re :		fclean all

.PHONY : all clean fclean re clear compiling cleaning
