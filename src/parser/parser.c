/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/07 20:19:50 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

//	arr[0] = variable to check if you are in a single quote
//	arr[1] = variable to check if you are in a double quote
//	arr[2] = variable to check if you are in or out of any type of quotes
//	arr[3] = variable that contains the number of quotes in a word
//	arr[4] = variable that contains the starting point of the word

void	set_int_arr(int *arr)
{
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 1;
	arr[3] = 0;
	arr[4] = 0;
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

void	check_if_word(char *str, int *arr, int *counts, int *len_words)
{
	if ((str[counts[1]] == ' ' && arr[2])
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

/*
int	*calculate_length(char *str, int *len_words, int *arr, int *counts)
{
	int	i;

//	i = -1;
	set_int_arr(arr, counts);
	if (str[counts[1] + 1] == ' ' && counts[1] == -1)
		while (str[counts[1] + 1] == ' ')
			counts[1]++;
	len_words[0] = counts[1] + 1;
	counts[4] = 1;
	while (str[++counts[1]])
	{
		if (str[counts[1]] == ' ' && str[counts[1] - 1] == ' ' && arr[2])
			continue ;
		check_arr(&str[counts[1]], arr, counts);
		check_if_word(str, arr, counts, len_words);
//		if ((str[i] == ' ' && arr[2])
//			|| (str[i + 1] == '\0' && str[i] != ' '))
//			len_words[++word] = i;
	}
	i = -1;
	printf("Len lenght: %d\n", counts[4]);
	while (++i < counts[4])
		printf("Len words %d: %d\n", i, len_words[i]);
	return (len_words);
}
*/

/*
int	*count_words(char *str, int *words)
{
//	int	i;
	int	counts[5];
	int	arr[3];
	int	*len_words;

//	i = -1;
	set_int_arr(arr, counts);
	while (str[++counts[1]])
	{
		if (str[counts[1]] == ' ' && counts[1] == 0)
			while (str[counts[1]] == ' ')
				counts[1]++;
		if (str[counts[1]] == ' ' && str[counts[1] - 1] == ' ' && arr[2])
			continue ;
		check_arr(&str[counts[1]], arr, counts);
		check_if_word(str, arr, counts, NULL);
//		if ((str[i] == ' ' && arr[2])
//			|| (str[i + 1] == '\0' && str[i] != ' '))
//			(*words)++;
//		printf("C: %c, Single: %d, Double %d, Not_in_arr %d, Count %d\n", str[counts[1]], arr[0], arr[1], arr[2], counts[4]);
	}
	*words = counts[4];
	len_words = (int *)malloc(sizeof(int) * (counts[4] + 1));
	if (!len_words)
		return (NULL);
	return (calculate_length(str, len_words, arr, counts));
}
*/

/*
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
	if (correct_arr(split))
		return (free_int_arr(&len_words));
//	load_commands(tokens, split);
//	tokens->command = (t_command *)malloc(sizeof(t_command));
//	tokens->command->cmd = ft_strdup(split[0]);
//	tokens->command->args = split;
	tokens->command = NULL;
	free_int_arr(&len_words);
	return (0);
}
*/

int	add_word(t_parser **tmp, char *word)
{
	t_parser	*new;

	if (!(*tmp)->word)
	{
		(*tmp)->word = word;
		if (!(*tmp)->word)
		{
			free(word);
			return (1);
		}
	}
	else
	{
		new = (t_parser *)malloc(sizeof(t_parser));
		if (!new)
		{
			free(word);
			return (1);
		}
		new->word = word;
		new->next = NULL;
//		printf("Here Tmp: %p\n", *tmp);
		(*tmp)->next = new;
		(*tmp) = (*tmp)->next;
//		printf("Then Tmp: %p\n", *tmp);
	}
	return (0);
}

int	create_word(t_parser **tmp, char *string, int k, int len)
{
	char	*word;

	if (string[k + len + 1] == '\0')
		len++;
	word = ft_substr(string, k, len);
	if (!word)
		return (1);
	if (add_word(tmp, word))
		return (1);
	return (0);
}

int	find_more_words(t_parser **tmp, char *string, int *arr, int i)
{
	int			k;

	k = arr[4] - 1;
	while (++k < i)
	{
		if (string[k] == '<' || string[k] == '>' || string[k] == '|')
		{
			if (k == arr[4])
			{
				if (create_word(tmp, string, k, 1))
					return (1);
				arr[4]++;
				continue ;
			}
			if (create_word(tmp, string, arr[4], k - arr[4]))
				return (1);
			if (create_word(tmp, string, k, 1))
				return (1);
			arr[4] = k + 1;
		}
	}
//	printf("Arr 4: %d\tK: %d\tI: %d\n", arr[4], k, i);
	if (i != arr[4] && create_word(tmp, string, arr[4], k - arr[4]))
		return (1);
	arr[4] = k;
	return (0);
}

int	find_word(t_parser **tmp, char *string, int *arr, int i)
{
	char	*word;

	check_quotes(&string[i], arr);
	if ((string[i] == ' ' && arr[2])
		|| (string[i + 1] == '\0' && string[i] != ' '))
	{
		if (arr[3])
		{
			if (string[i + 1] == '\0')
				word = ft_substr(string, arr[4], i - arr[4] + 1);
			else
				word = ft_substr(string, arr[4], i - arr[4]);
			if (!word)
				return (1);
			if (add_word(tmp, word))
				return (1);
		}
		else if(find_more_words(tmp, string, arr, i))
			return (1);
		arr[3] = 0;
	}
	return (0);
}

int	if_conds(char *string, int *arr, int *i)
{
	if (string[*i] == ' ' && *i == 0 && arr[2])
		while (string[*i] == ' ')
			(*i)++;
	if (string[*i - 1] == ' ' && string[*i] == ' ' && arr[2])
		return (1);
	else if (string[*i - 1] == ' ' && string[*i] != ' ' && arr[2])
		arr[4] = *i;
	return (0);
}

int	parse_string(t_minishell *tokens, t_parser *split, char *string)
{
	int			i;
	int			start;
	int			arr[5];
	t_parser	*tmp;

	i = -1;
	start = 0;
	set_int_arr(arr);
	tmp = split;
	(void)tokens;
	while (string[++i])
	{
		if (if_conds(string, arr, &i))
			continue ;
		if (find_word(&tmp, string, arr, i))
			return (MALLOC);
//		printf("Split %p\tTmp: %p\n", split, tmp);
	}
	tmp = split;
	while (tmp)
	{
		printf("Word:-->%s--<\n", tmp->word);
		tmp = tmp->next;
	}
	return (0);
}

int	parser(t_minishell *tokens, char *env[], char *string)
{
	t_parser	*split;

	(void)env;
	if (count_quotes(string))
	{
		free_tokens(&tokens);
		return (SYNTAX);
	}
	split = (t_parser *)malloc(sizeof(t_parser));
	if (!split)
	{
		free_tokens(&tokens);
		return (MALLOC);
	}
	split->word = NULL;
	split->next = NULL;
	return (parse_string(tokens, split, string));
}
