/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/03 20:12:35 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	*calculate_length(char *str, int *len_words)
{
	int	i;
	int	word;
	int	quotes[3];

	i = -1;
	word = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	quotes[2] = 1;
	if (str[i + 1] == ' ' && i == -1)
		while (str[i + 1] == ' ')
			i++;
	len_words[0] = i + 1;
	while (str[++i])
	{
		if (str[i] == ' ' && str[i - 1] == ' ' && quotes[2])
			continue ;
		quotes_check(&str[i], quotes);
		if ((str[i] == ' ' && quotes[2])
			|| (str[i + 1] == '\0' && str[i] != ' '))
			len_words[++word] = i;
	}
	i = -1;
	while (++i <= word)
		printf("Len words %d: %d\n", i, len_words[i]);
	return (len_words);
}

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

int	*count_words(char *str, int *words)
{
	int	i;
	int	quotes[3];
	int	*len_words;

	i = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	quotes[2] = 1;
	while (str[++i])
	{
		if (str[i] == ' ' && i == 0)
			while (str[i] == ' ')
				i++;
		if (str[i] == ' ' && str[i - 1] == ' ' && quotes[2])
			continue ;
		quotes_check(&str[i], quotes);
		if ((str[i] == ' ' && quotes[2])
			|| (str[i + 1] == '\0' && str[i] != ' '))
			(*words)++;
//		printf("C: %c, Single: %d, Double %d, Not_in_quotes %d, Count %d\n", str[i], quotes[0], quotes[1], quotes[2], *words);
	}
	len_words = (int *)malloc(sizeof(int) * (*words + 1));
	if (!len_words)
		return (NULL);
	return (calculate_length(str, len_words));
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
		return (free_len(&len_words));
	if (fill_words(split, str, len_words, index))
		return (free_len(&len_words));
	while (++i < index)
		printf("Word: %s-->\n", split[i]);
	if (correct_quotes(split))
		return (free_len(&len_words));
//	load_commands(tokens, split);
	tokens->command = (t_command *)malloc(sizeof(t_command));
	tokens->command->cmd = ft_strdup(split[0]);
	tokens->command->args = split;
	tokens->command->next = NULL;
	free_len(&len_words);
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
