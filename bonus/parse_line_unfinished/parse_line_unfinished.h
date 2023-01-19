/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_unfinished.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:33:32 by averdon           #+#    #+#             */
/*   Updated: 2023/01/10 17:41:31 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_LINE_UNFINISHED_H

# define PARSE_LINE_UNFINISHED_H

int		links_command_closed(char *line, int mode);
int		paranthesis_closed(char *line, int mode);
int		quotes_closed(char *command);
int		line_unfinished(char **line, int mode);
char	*put_space_parsing(char *line);

#endif
