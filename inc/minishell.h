/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:14:15 by vduchi            #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "pipes.h"
# include "built-ins.h"
# include "parser.h"

enum
{
	MALLOC = 1,
	SYNTAX,
	PIPE_FIRST,
	ONLY_REDIR,
	OPEN_FAILED,
};

const static char	*g_error_array[] = {
	"malloc error", \
	"syntax error", \
	"syntax error near unexpected token `|\'", \
	"syntax error near unexpected token `newline\'", \
	"Open error: ", \
};

int		d_key(void);
int		end_program(char **string, int error);

void	siginthandler(int sig);
void	free_double(char **dbl);
void	free_tokens(t_minishell **tokens);

char	*ft_find_path(char *env[]);

#endif
