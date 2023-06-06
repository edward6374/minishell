/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/06 17:58:48 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

char	*take_word(char *str, int *len_words, int i, int index)
{
	int		l;
	char	*new;

	l = len_words[i];
	while (str[l] == ' ')
		l++;
	if (i == (index - 1) && str[len_words[i + 1]] != ' '
		&& str[len_words[i + 1] + 1] == '\0')
		new = ft_substr(str, l, len_words[i + 1] - l + 1);
	else
		new = ft_substr(str, l, len_words[i + 1] - l);
	return (new);
}

int	fill_words(char **split, char *str, int *len_words, int index)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		split[i] = take_word(str, len_words, i, index);
		if (!split[i])
			return (free_split(split, i));
	}
	split[i] = NULL;
	return (0);
}

//	quotes[0] = variable to check if you are in a single quote
//	quotes[1] = variable to check if you are in a double quote
//	quotes[2] = variable to check if you are in or out of any type of quotes
//	counts[0] = index of where is the first character of a word
//	counts[1] = counter to loop a string
//	counts[2] = number of single quotes in the whole string
//	counts[3] = number of double quotes in the whole string
//	counts[4] = variable used to count the number of words or to loop through the len_words

void	set_int_arr(int *quotes, int *counts)
{
	quotes[0] = 0;
	quotes[1] = 0;
	quotes[2] = 1;
	counts[0] = 0;
	counts[1] = -1;
	counts[2] = 0;
	counts[3] = 0;
	counts[4] = 0;
}

void	if_pipe_or_redir(char *str, int *counts, int *len_words)
{
	int	i;

	i = counts[0] - 1;
	while (++i < counts[1])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if (!len_words)
				counts[4] = counts[4] + 2;
			else
			{
				if ((str[i + 1] == '<' || str[i + 1] == '>')
						&& str[i] != '|')
				{
					len_words[counts[4]] = i;
					len_words[counts[4] + 1] = i + 2;
					i++;
				}
				else
				{
					len_words[counts[4]] = i;
					len_words[counts[4] + 1] = i + 1;
				}
				counts[4] = counts[4] + 2;
			}
		}
	}
}

void	check_if_word(char *str, int *quotes, int *counts, int *len_words)
{
	if ((str[counts[1]] == ' ' && quotes[2])
		|| (str[counts[1] + 1] == '\0' && str[counts[1]] != ' '))
	{
		if (counts[2] == 0 && counts[3] == 0)
			if_pipe_or_redir(str, counts, len_words);
		else
		{
			if (len_words)
				len_words[counts[4]] = counts[1];
			counts[4]++;
		}
		counts[0] = counts[1];
	}
}

int	*calculate_length(char *str, int *len_words, int *quotes, int *counts)
{
	int	i;

//	i = -1;
	set_int_arr(quotes, counts);
	if (str[counts[1] + 1] == ' ' && counts[1] == -1)
		while (str[counts[1] + 1] == ' ')
			counts[1]++;
	len_words[0] = counts[1] + 1;
	counts[4] = 1;
	while (str[++counts[1]])
	{
		if (str[counts[1]] == ' ' && str[counts[1] - 1] == ' ' && quotes[2])
			continue ;
		check_quotes(&str[counts[1]], quotes, counts);
		check_if_word(str, quotes, counts, len_words);
//		if ((str[i] == ' ' && quotes[2])
//			|| (str[i + 1] == '\0' && str[i] != ' '))
//			len_words[++word] = i;
	}
	i = -1;
	printf("Len lenght: %d\n", counts[4]);
	while (++i < counts[4])
		printf("Len words %d: %d\n", i, len_words[i]);
	return (len_words);
}

int	*count_words(char *str, int *words)
{
//	int	i;
	int	counts[5];
	int	quotes[3];
	int	*len_words;

//	i = -1;
	set_int_arr(quotes, counts);
	while (str[++counts[1]])
	{
		if (str[counts[1]] == ' ' && counts[1] == 0)
			while (str[counts[1]] == ' ')
				counts[1]++;
		if (str[counts[1]] == ' ' && str[counts[1] - 1] == ' ' && quotes[2])
			continue ;
		check_quotes(&str[counts[1]], quotes, counts);
		check_if_word(str, quotes, counts, NULL);
//		if ((str[i] == ' ' && quotes[2])
//			|| (str[i + 1] == '\0' && str[i] != ' '))
//			(*words)++;
//		printf("C: %c, Single: %d, Double %d, Not_in_quotes %d, Count %d\n", str[counts[1]], quotes[0], quotes[1], quotes[2], counts[4]);
	}
	*words = counts[4];
	len_words = (int *)malloc(sizeof(int) * (counts[4] + 1));
	if (!len_words)
		return (NULL);
	return (calculate_length(str, len_words, quotes, counts));
}

int	parse_string(t_minishell *tokens, char *str)
{
	int			i;
	int			index;
	int			*len_words;
	char		**split;

	i = -1;
	index = 0;
	len_words = count_words(str, &index);
	if (!len_words)
		return (1);
	split = (char **)malloc(sizeof(char *) * (index + 1));
	//	Tutto qua sotto da errore vecio al compilare 😳
	if (!split)
		return (free_int_arr(&len_words));
	if (fill_words(split, str, len_words, index))
		return (free_int_arr(&len_words));
	while (++i < index)
		printf("Word: %s-->\n", split[i]);
	if (correct_quotes(split))
		return (free_int_arr(&len_words));
//	load_commands(tokens, split);
//	tokens->command = (t_command *)malloc(sizeof(t_command));
//	tokens->command->cmd = ft_strdup(split[0]);
//	tokens->command->args = split;
	tokens->command = NULL;
	free_int_arr(&len_words);
	return (0);
}

int	parser(t_minishell *tokens, char *env[], char *string)
{
	(void)env;
	if (count_quotes(string))
	{
		free_tokens(&tokens);
		return (SYNTAX);
	}
	return (parse_string(tokens, string));
}
