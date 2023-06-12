/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/09 12:46:14 by vduchi           ###   ########.fr       */
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

#endif
