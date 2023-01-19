/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:28:08 by averdon           #+#    #+#             */
/*   Updated: 2022/12/16 13:08:25 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

# define BUILTINS_H

# include "cd/cd.h"
# include "echo/echo.h"
# include "env/env.h"
# include "exit/exit.h"
# include "export/export.h"
# include "pwd/pwd.h"
# include "unset/unset.h"
# include "../minishell.h"

int	main_builtins(int argc, char **argv, int pid, t_arg *arg);

#endif
