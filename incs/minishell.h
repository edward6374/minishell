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

enum
{
	MALLOC = 1,
	SYNTAX,
	PIPE_FIRST,
	ONLY_REDIR,
	OPEN_FAILED,
	CMD_NOT_FOUND,
	CMD_FOUND_NOT_EX,
	FILE_NOT_READ,
	FILE_NOT_WRITE,
	GETCWD_ERROR,
	PIPE_ERROR,
	DUP_ERROR,
	PATH_ERROR,
};

const static char	*g_error_array[] = {
	"malloc error", \
	"syntax error", \
	"syntax error near unexpected token `|\'", \
	"syntax error near unexpected token `newline\'", \
	"Open error", \
	"command not found", \
	"Permission error", \
	"File not readable", \
	"File not writeable", \
	"Getcwd() error", \
	"Error creating pipe", \
	"Error creating dup", \
	"no such file or directory: ", \
	"numeric argument required", \
};

typedef struct	s_here_doc
{
	int		first;
	int		if_hdoc;
	int		fd_hdoc[2];
	char	*stop_word;
}	t_here_doc;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*before;
}	t_env;

typedef struct	s_parser
{
	char			*word;
	struct s_parser	*next;
	struct s_parser	*before;
}	t_parser;

typedef struct s_cmd
{
	int				n;
	int				ok;
	int				in_fd;
	int				out_fd;
	char			*cmd;
	char			**args;
	t_here_doc		*here_doc;
	struct s_cmd	*next;
	struct s_cmd	*before;
}	t_cmd;

typedef struct s_min
{
	int		num_cmds;
	int		exit_value;
	char	**path;
	t_env	*env;
	t_cmd	*cmds;
}	t_min;

# include "libft.h"
# include "parser.h"
# include "execute.h"
# include "built-ins.h"
# include "library/include/readline/readline.h"
# include "library/include/readline/history.h"

/* ---			Utils.c				--- */
int			d_key(void);
int			end_program(char **string, int error);
void		siginthandler(int sig);
void		exit_error(const char *str, int i);
char		*ft_find_path(char *env[]);

/* ---			Free_funcs.c			--- */
int			free_pointer(void *pt, int out);
int			free_double_int(char **old, int i);
void		free_double_void(char **old);
char		**free_double_char(char **old, int i);
t_min		*free_struct(t_min **tk);

/* ---			Free_tokens.c			--- */
int			free_env(t_env **first);
void		free_commands(t_cmd **first);
int			free_tokens(t_min **tk, t_parser **temp, int out);

#endif
