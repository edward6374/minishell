/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:40:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/12 17:40:53 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_word(t_parser **temp, char *word)
{
	t_parser	*new;

	printf("Bef\tTemp: %p\tAdd word: --%s--\n", *temp, (*temp)->word);
	if (!(*temp)->word)
	{
		printf("Empty temp\n");
		(*temp)->word = word;
	}
	else
	{
		printf("Next temp\n");
		new = (t_parser *)malloc(sizeof(t_parser));
		if (!new)
			return (free_pointer(word, MALLOC));
		new->word = word;
		new->next = NULL;
		new->before = (*temp);
		(*temp)->next = new;
		(*temp) = (*temp)->next;
		new = NULL;
	}
	printf("After\tTemp: %p\tAdd word: --%s--\n", *temp, (*temp)->word);
	return (0);
}

int	create_word(t_parser **temp, t_vars *v, int *k, int mode)
{
	int		len;
	char	*word;

	printf("Create word: Idx: %d\tStart: %d\tCar start: --%c--\tCar Idx: --%c--\n", *k, v->stp, v->s[v->stp], v->s[*k]);
	if (!mode)
	{
		printf("Mode 0\n");
		len = 1;
		if ((v->s[*k] == '<' && v->s[*k + 1] == '<')
			|| (v->s[*k] == '>' && v->s[*k + 1] == '>'))
		{
			len++;
			(*k)++;
		}
	}
	else
	{
		printf("Mode 1\n");
		len = *k - v->stp;
		if (!len)
			return (0);
	}
	printf("Len: %d\n", len);
	word = ft_substr(v->s, v->stp, len);
	if (!word || add_word(temp, word))
		return (MALLOC);
	v->stp += len;
	printf("End start: %d\n\n", v->stp);
	return (0);
}

int	find_more_words(t_parser **temp, t_vars *v)
{
	int	k;

	k = v->stp - 1;
	printf("\nBefore: Arr 4: %d\tK: %d\tI: %d\n", v->stp, k, v->i);
	while (++k < v->i)
	{
		if (v->s[k] == '<' || v->s[k] == '>'
			|| v->s[k] == '|')
		{
			if (k - v->stp > 0 && create_word(temp, v, &k, 1))
				return (MALLOC);
			if (create_word(temp, v, &k, 0))
				return (MALLOC);
		}
	}
	printf("After:  Arr 4: %d\tK: %d\tI: %d\n", v->stp, k, v->i);
	if (v->s[v->i + 1] == '\0' && v->s[v->i] != ' ')
		k++;
	if (create_word(temp, v, &k, 1))
		return (MALLOC);
	return (0);
}

int	find_word(t_parser **temp, t_vars *v)
{
	check_quotes(v, v->s[v->i]);      // This function is used to count the number of quotes and to check
                                                // whether you are in a simple or double quote or in neither of those
	if (((v->s[v->i] == ' ' && v->oq) // This if is used to take a word, or multiple words if they are
		|| (v->s[v->i + 1] == '\0' && v->s[v->i] != ' '))) // all together and you put some special symbols into a single word
	{
		if (v->nq && take_words_with_quotes(temp, v))   // This variable is to check if your word has quotes or not
			return (MALLOC);
		else if (!v->nq && find_more_words(temp, v))
			return (MALLOC);
		v->nq = 0;
	}
	return (0);
}
