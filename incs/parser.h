/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/28 15:54:36 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// int i;	// variable used to loop through str
// int sq; // single_quotes -> variable used to check if you are in a
//  single quote
// int dq; // double_quotes -> variable used to check if you are
//  in a double quote
// int oq; // out_quotes -> variable used to check if you are in any quotes
// // int nq;		// number_quotes -> variable that is the number
// of quotes in a word
// int stp; // starting_point -> variable that is the starting point of a word
// // int count; // variable to used to checkk if a env variable
//  is after another one
// char *s; // string -> variable that represent the string came fom readline

# include "minishell.h"

typedef struct s_space
{
	int		i;
	int		j;
	int		len;
	int		space;
}			t_space;

typedef struct s_vars
{
	int		i;
	int		sq;
	int		dq;
	int		oq;
	int		stp;
	char	*s;
}			t_vars;

typedef struct s_lastword
{
	int		i;
	int		l;
	int		*idx;
	int		count;
	int		check;
	char	*word;
}			t_word;

typedef struct s_check
{
	int		len;
	char	*new;
}			t_check;

typedef struct s_path_env
{
	int		i;
	int		num_paths;
	char	*res;
	char	*token;
	char	**paths;
	char	*path_copy;
}			t_path_env;

/* ---			Cmd_and_args.c			--- */
int			add_arguments(t_parser **list, t_cmd *new);
int			add_command(t_min **tk, t_parser **list, t_cmd *new);
t_cmd		*set_new_command(int *number);

/* ---			Create_tokens.c				--- */
int			load_commands(t_min *tk, t_parser *list);

/* ---			Env_var.c			--- */
int			check_env_word(t_parser **word_lst, t_env **env, t_vars *v, int *i);
t_env		*find_env_vars(t_env *env, t_vars *v);

/* ---			Env_utils.c			--- */
char		*check_spaces(t_env **env, char *str);
int			add_env_var(t_word *w, t_env **env);
t_env		*search_env(t_env *env, void *data_ref, int (*cmp)(char *, char *,
					int));

/* ---			Handle_quotes.c				--- */
int			count_quotes(char *string);
int			words_dbl_qts(t_parser **word_lst, t_vars *v, t_env **env,
				int *idx);
int			words_sin_qts(t_parser **word_lst, t_vars *v, t_env **env,
				int *idx);
void		check_quotes(t_vars *vars, char *c);

/* ---			Handle_words.c			--- */
int			add_word(t_parser **word_lst, char *word);
int			join_words(t_parser **word_lst, char *word);
int			create_word(t_parser **word_lst, t_vars *v, int *i, int mode);
int			add_or_join(t_parser **word_lst, t_vars *v, char *word, int mode);
int			multiple_words(t_parser **word_lst, t_env **env, t_vars *v,
				int end);

/* ---			Parser.c			--- */
int			parser(t_min *tk, char *line);
int			add_word(t_parser **tmp, char *word);

/* ---			Path_env.c			--- */
char		**path_env(t_env *env);

/* ---			Redirections.c			--- */
int			take_redir(t_parser **tmp, t_cmd *new);

/* ---			Pars_utils.c			--- */
int			check_access(char *to_free, char *str, int mode);
int			end_refill(t_parser **word_lst, t_vars *v, t_word *w);
void		set_vars(t_vars *v, char *s);
t_cmd		*get_last_cmd(t_min **tk);
t_cmd		*set_new_command(int *number);

#endif
