/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/13 19:27:33 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_vars
{
	int		i;				// variable used to loop through str
	int		sin_qts;		// single_quotes -> variable used to check if you are in a single quote
	int		dbl_qts;		// double_quotes -> variable used to check if you are in a double quote
	int		out_qts;		// out_quotes -> variable used to check if you are in any quotes
	int		num_qts;		// number_quotes -> variable that is the number of quotes in a word
	int		start_point;	// starting_point -> variable that is the starting point of a word
	char	*str;			// string -> variable that represent the string came fom readline
}	t_vars;

int		free_int_arr(int **len_words);
int		free_split(char **split, int i);
int		free_split_with_index(char **split, int index, int i);
char	**free_my_split(char **split, int **len_words, int i);

int		count_quotes(char *string);
int		correct_quotes(char **split);
void	check_quotes(t_vars *vars, char *c);

int		load_commands(t_minishell *tokens, t_parser *split);

/* ---			Parser.c			--- */
int		add_word(t_parser **tmp, char *word);
int		parser(t_minishell *tokens, char *env[], char *string);

/* ---			Cmd_and_args.c			--- */
int			add_arguments(t_parser **split, t_command *new);
int			add_command(t_minishell **tokens, t_parser **split, t_command *new);
t_command	*set_new_command(int *number);

/* ---			Redirections.c			--- */
int	take_redir(t_parser **tmp, t_command *new);

/* ---			Env_var.c			--- */
int	check_env_var(t_parser **temp, t_vars *vars, char *env[]);

#endif
