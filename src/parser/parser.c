/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/09 13:24:46 by vduchi           ###   ########.fr       */
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
/*
int	next_word(t_parser **tmp, char *word)
{

	new = (t_parser *)malloc(sizeof(t_parser));
	if (!new)
	{
		free(word);
		return (1);
	}
	new->word = word;
	new->next = NULL;
	new->before = (*tmp);
	//		printf("Here Tmp: %p\n", *tmp);
	(*tmp)->next = new;
	(*tmp) = (*tmp)->next;
	//		printf("Then Tmp: %p\n", *tmp);
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
		new->before = (*tmp);
		//		printf("Here Tmp: %p\n", *tmp);
		(*tmp)->next = new;
		(*tmp) = (*tmp)->next;
		//		printf("Then Tmp: %p\n", *tmp);
	}
//		next_word(tmp, word);
	return (0);
}

int	create_word(t_parser **tmp, char *string, int k, int len)
{
	char	*word;

	if (string[k + len + 1] == '\0')
		len++;
//	printf("K: %d\tLen: %d\n", k, len);
	if (!len)
		return (0);
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
	if (create_word(tmp, string, arr[4], k - arr[4]))
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
		else if (find_more_words(tmp, string, arr, i))
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
	}
	tmp = split;
	while (tmp)
	{
		printf("Tmp:-->%p\n", tmp);
		printf("Word:-->%s--<\n", tmp->word);
		printf("Next:-->%p\n", tmp->next);
		printf("Before:-->%p\n\n", tmp->before);
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
	split->before = NULL;
	if (parse_string(tokens, split, string))
	{
		free_tokens(&tokens);
		return (MALLOC);
	}
	return (load_commands(tokens, split));
//	return (0);
}
