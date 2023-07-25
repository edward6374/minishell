/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/25 20:12:41 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_vars
{
	int		i;				// variable used to loop through str
	int		count;			// variable to used to checkk if a env variable is after another one
	int		sin_qts;		// single_quotes -> variable used to check if you are in a single quote
	int		dbl_qts;		// double_quotes -> variable used to check if you are in a double quote
	int		out_qts;		// out_quotes -> variable used to check if you are in any quotes
	int		num_qts;		// number_quotes -> variable that is the number of quotes in a word
	int		start_point;	// starting_point -> variable that is the starting point of a word
	char	*s;			// string -> variable that represent the string came fom readline
}	t_vars;

int		free_pointer(void *pt, int out);

int		check_name(char *s, char *value);

int		count_quotes(char *string);
int		correct_quotes(char **split);
void	check_quotes(t_vars *vars, char *c);

int		load_commands(t_min *tk, t_parser *split);

/* ---			Parser.c			--- */
int		add_word(t_parser **tmp, char *word);
int		parser(t_min *tk, char *env[], char *string);

/* ---			Cmd_and_args.c			--- */
int		add_arguments(t_parser **split, t_cmd *new);
int		add_command(t_min **tk, t_parser **split, t_cmd *new);
t_cmd	*set_new_command(int *number);

/* ---			Redirections.c			--- */
int	take_redir(t_parser **tmp, t_cmd *new);

/* ---			Env_var.c			--- */
int	check_env_var(t_parser **temp, t_vars *vars, char *env[]);

#endif
