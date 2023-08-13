/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:14:15 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/13 18:31:00 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <errno.h>
// # include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>

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

const static char *g_error_array[] = {
	"malloc error",
	"syntax error",
	"syntax error near unexpected token `|\'",
	"syntax error near unexpected token `newline\'",
	"Open error",
	"command not found",
	"Permission error",
	"File not readable",
	"File not writeable",
	"Getcwd() error",
	"Error creating pipe",
	"Error creating dup",
	"no such file or directory: ",
	"numeric argument required",
};

typedef struct s_here_doc
{
	int		first;
	int		if_hdoc;
	int		fd_hdoc[2];
	char	*stop_word;
}	t_here_doc;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*before;
}	t_env;

typedef struct s_parser
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

// # include "built-ins.h"
# include "execute.h"
# include "history.h"
# include "libft.h"
# include "parser.h"
# include "readline.h"

/* ---			Take_env.c			--- */
int	take_env(t_min *tk, char *env[]);

/* ---			Utils.c				--- */
int		d_key(t_min **tk);
int		end_program(char **line, int error);
void	exit_error(const char *str, int i);
char	*ft_find_path(char *env[]);

/* ---			Free_funcs.c			--- */
int		free_pointer(void *pt, int out);
int		free_double_int(char **old, int i);
void	free_double_void(char **old);
char	**free_double_char(char **old, int i);

/* ---			Free_structs.c			--- */
int		free_env(t_env *first);
int		free_all(t_min *tk, int out);
int		free_parser(t_parser *words, int out);
void	free_commands(t_cmd **first);

#endif
