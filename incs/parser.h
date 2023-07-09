/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/09 12:39:52 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct	s_parser
{
	char			*word;
	struct s_parser	*next;
	struct s_parser	*before;
}	t_parser;

int		free_int_arr(int **len_words);
int		free_split(char **split, int i);
int		free_split_with_index(char **split, int index, int i);

int		count_quotes(char *string);
int		correct_quotes(char **split);
void	check_quotes(char *c, int *quotes);

int		load_commands(t_minishell *tokens, t_parser *split);
int		parser(t_minishell *tokens, char *env[], char *string);

char	**free_my_split(char **split, int **len_words, int i);

/* ---			Cmd_and_args.c			--- */
int			add_arguments(t_parser **split, t_command *new);
int			add_command(t_minishell **tokens, t_parser **split, t_command *new);
t_command	*set_new_command(int *number);

/* ---			Redirections.c			--- */
int	take_redir(t_parser **tmp, t_command *new);

/* ---			Env_var.c			--- */
int	check_env_var(t_parser **temp, char *env[], char *c, int *arr);

#endif
