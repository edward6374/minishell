/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 18:41:53 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_vars
{
	int		i;		// variable used to loop through str
	int		count;	// variable to used to checkk if a env variable is after another one
	int		sq;		// single_quotes -> variable used to check if you are in a single quote
	int		dq;		// double_quotes -> variable used to check if you are in a double quote
	int		oq;		// out_quotes -> variable used to check if you are in any quotes
	int		nq;		// number_quotes -> variable that is the number of quotes in a word
	int		stp;	// starting_point -> variable that is the starting point of a word
	char	*s;		// string -> variable that represent the string came fom readline
}	t_vars;

/* ---			Cmd_and_args.c			--- */
int		add_arguments(t_parser **list, t_cmd *new);
int		add_command(t_min **tk, t_parser **list, t_cmd *new);
t_cmd	*set_new_command(int *number);

/* ---			Create_tokens.c				--- */
int		load_commands(t_min *tk, t_parser *list);

/* ---			Env_var.c			--- */
int		check_env_var(t_min *tk, t_parser **temp, t_vars *vars);

/* ---			Handle_quotes.c				--- */
int		count_quotes(char *string);
int		take_words_with_quotes(t_parser **temp, t_vars *v);

/* ---			Handle_words.c			--- */
int		find_word(t_parser **temp, t_vars *v);
int		create_word(t_parser **temp, t_vars *v, int *k, int mode);

/* ---			Parser.c			--- */
int		parser(t_min *tk, char *line);
int		add_word(t_parser **tmp, char *word);

/* ---			Redirections.c			--- */
int		take_redir(t_parser **tmp, t_cmd *new);

/* ---			Utils.c			--- */
int		check_access(char *str, int mode);
void	set_vars(t_vars *v, char *s);
void	check_quotes(t_vars *vars, char c);
t_cmd	*get_last_cmd(t_min **tk);
t_cmd	*set_new_command(int *number);

#endif
