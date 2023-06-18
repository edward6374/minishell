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

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "libft.h"
# include "library/include/readline/readline.h"
# include "library/include/readline/history.h"

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

typedef struct s_command
{
	int					ok;
	int					in;
	int					out;
	char				*cmd;
	char				**args;
	struct s_command	*next;
	struct s_command	*before;
}	t_command;

typedef struct s_minishell
{
	int			num_comms;
	char		**path;
	t_command	*command;
}	t_minishell;

# include "pipes.h"
# include "built-ins.h"
# include "parser.h"

int		d_key(void);
int		end_program(char **string, int error);

void	siginthandler(int sig);
void	free_double(char **dbl);
void	free_tokens(t_minishell **tokens);

char	*ft_find_path(char *env[]);

#endif
