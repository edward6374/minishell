/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:41:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/03 19:07:01 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int		free_len(int **len_words);
int		free_split(char **split, int i);
int		free_split_with_index(char **split, int index, int i);

int		count_quotes(char *string);
int		correct_quotes(char **split);
int		load_commands(t_minishell *tokens, char **split);
int		parser(t_minishell *tokens, char *env[], char *string);

void	quotes_check(char *c, int *quotes);

char	**free_my_split(char **split, int **len_words, int i);

#endif
