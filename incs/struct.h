/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:17:00 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/09/02 11:09:04 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

extern unsigned char	g_exit;

# define NO_COLOR "\033[0;0m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define BLACK "\033[0;99m"
# define ORANGE "\033[38;5;209m"
# define BROWN "\033[38;2;184;143;29m"
# define DARK_GRAY "\033[38;5;234m"
# define MID_GRAY "\033[38;5;245m"
# define DARK_GREEN "\033[38;2;75;179;82m"
# define DARK_YELLOW "\033[38;5;143m"

# define TERROR "\xF0\x9F\x98\xB1"

enum
{
	MALLOC = 1,
	SYNTAX,
	PIPE_FIRST,
	ONLY_REDIR,
	OPEN_FAILED,
	CMD_NOT_FOUND,
	CMD_FOUND_NOT_EX,
	FILE_NOT_FOUND,
	FILE_NOT_READ,
	FILE_NOT_WRITE,
};

const static char		*g_error_array[] = {
	"Malloc error",
	"Syntax error",
	"syntax error near unexpected token `|\'",
	"syntax error near unexpected token `newline\'",
	"open error",
	"command not found",
	"permission denied",
	"no such file or directory",
	"file not readable",
	"file not writeable",
};

typedef struct s_here_doc
{
	int					yes;
	int					first;
	int					fd[2];
	char				*stop;
}						t_here_doc;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*before;
}						t_env;

typedef struct s_parser
{
	char				*word;
	struct s_parser		*next;
	struct s_parser		*before;
}						t_parser;

typedef struct s_cmd
{
	int					n;
	int					ok;
	int					in_fd;
	int					out_fd;
	char				*cmd;
	char				*err_f;
	char				**args;
	t_here_doc			*hdoc;
	struct s_cmd		*next;
	struct s_cmd		*before;
}						t_cmd;

typedef struct s_min
{
	int					num_cmds;
	char				**pt_env;
	t_env				*env;
	t_cmd				*cmds;
	char				*pwd;
	char				*oldpwd;
	char				*home;
}						t_min;

#endif
