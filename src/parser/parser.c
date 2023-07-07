/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/07 14:48:00 by vduchi           ###   ########.fr       */
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

int	add_word(t_parser **tmp, char *word)
{
	t_parser	*new;

//	printf("Add word: --%s--\n", word);
	if (!(*tmp)->word)
		(*tmp)->word = word;
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
	return (0);
}

int	create_word(t_parser **tmp, char *string, int *k, int len)
{
	char	*word;

	if (string[*k + len + 1] == '\0' && string[*k + len] != ' ')
		len++;
//	printf("Create: Arr 4: %d\tLen: %d\n", *k, len);
	if ((string[*k] == '<' && string[*k + 1] == '<')
		|| (string[*k] == '>' && string[*k + 1] == '>'))
	{
		word = ft_substr(string, *k, len + 1);
		(*k)++;
	}
	else
		word = ft_substr(string, *k, len);
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
//	printf("Before: Arr 4: %d\tK: %d\tI: %d\n", arr[4], k, i);
	while (++k < i)
	{
		if (string[k] == '<' || string[k] == '>' || string[k] == '|')
		{
			if (k == arr[4])
			{
				if (create_word(tmp, string, &k, 1))
					return (1);
				arr[4] = k + 1;
				continue ;
			}
			if (create_word(tmp, string, &arr[4], k - arr[4]))
				return (1);
			if (create_word(tmp, string &k, 1))
				return (1);
			arr[4] = k + 1;
		}
	}
//	printf("After:  Arr 4: %d\tK: %d\tI: %d\n", arr[4], k, i);
	if (k != arr[4] && create_word(tmp, string, &arr[4], k - arr[4]))
		return (1);
//	printf("Word: ---%s---\n", (*tmp)->word);
	return (0);
}

int	find_word(t_parser **tmp, char *string, int *arr, int i)
{
	char	*word;

	check_quotes(&string[i], arr);	// This function is used to count the number of quotes and to check
									// whether you are in a simple or double quote or in neither of those
	if ((string[i] == ' ' && arr[2])	// This if is used to take a word, or multiple words if they are
		|| (string[i + 1] == '\0' && string[i] != ' ')) // all together and you put some special symbols into a single word
	{
		if (arr[3])	// This variable is to check if your word has quotes or not
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
	if (string[*i] == ' ' && *i == 0 && arr[2])	// This if is to check whether you have one or multiple spaces	
		while (string[*i] == ' ')				// at the beginning of the string
			(*i)++;
	if (string[*i - 1] == ' ' && string[*i] == ' ' && arr[2])	// This if is to check whether you have one
		return (1);												// or multiple spaces in the middle of the string
	else if ((string[*i - 1] == ' ' || *i == 0) && string[*i] != ' ' && arr[2])
		arr[4] = *i;											// This if is to set the variable arr[4] to the
	return (0);													// first character of every word
}

int	parse_string(t_parser *all_words, char *string)
{
	int			i;
	int			start;
	int			arr[5];
	t_parser	*temp;

	i = -1;
	start = 0;
	set_int_arr(arr);	// Here I set the array values one by one to start
	temp = all_words;	// This temp is the one used to create every word, since the pointer 'all_words'
	while (string[++i])	// has always to point to the first word
	{
		if (if_conds(string, arr, &i))	// Here I check whether I am at the end of a word or if I have multiple spaces
			continue ;
		if (find_word(&temp, string, arr, i))	// Here I find the words or the multiple words to put
			return (MALLOC);					// into the all_words structure
	}
	temp = all_words;
	while (temp)	// This while is just for printing the resulted structure
	{
		printf("Temp:-->%p\n", temp);
		printf("Word:-->%s--<\n", temp->word);
		printf("Next:-->%p\n", temp->next);
		printf("Before:-->%p\n\n", temp->before);
		temp = temp->next;
	}
	return (0);
}

int	parser(t_minishell *tokens, char *env[], char *string)
{
	t_parser	*all_words;

	(void)env;
	if (count_quotes(string))	// If the line you write has a impair number of quotes, the program will just stop
		return (free_tokens(&tokens, SYNTAX));
	all_words = (t_parser *)malloc(sizeof(t_parser));
	if (!all_words)
		return (free_tokens(&tokens, MALLOC));
	all_words->word = NULL;
	all_words->next = NULL;
	all_words->before = NULL;
	if (parse_string(all_words, string))	// Here I parse the string and separate it into words
		return (free_tokens(&tokens, MALLOC));
	return (load_commands(tokens, all_words));	// Here I load all the words into commands in the main structure
}
