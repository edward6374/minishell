/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:40:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 14:52:07 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_word(t_parser **temp, char *word)
{
	t_parser	*new;

	if (!(*temp)->word)
		(*temp)->word = word;
	else
	{
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
	return (0);
}

int	create_word(t_parser **temp, t_vars *v, int *k, int mode)
{
	int		len;
	char	*word;

	if (!mode)
	{
		printf("Mode 0\n");
		len = 1;
		if ((v->s[*k] == '<' && v->s[*k + 1] == '<') || (v->s[*k] == '>'
				&& v->s[*k + 1] == '>'))
		{
			len++;
			(*k)++;
		}
	}
	else
	{
		len = *k - v->stp;
		if (!len)
			return (0);
	}
	word = ft_substr(v->s, v->stp, len);
	if (!word || add_word(temp, word))
		return (MALLOC);
	v->stp += len;
	return (0);
}

int	find_more_words(t_parser **temp, t_vars *v)
{
	int	k;

	k = v->stp - 1;
	while (++k < v->i)
	{
		if (v->s[k] == '<' || v->s[k] == '>' || v->s[k] == '|')
		{
			if (k - v->stp > 0 && create_word(temp, v, &k, 1))
				return (MALLOC);
			if (create_word(temp, v, &k, 0))
				return (MALLOC);
		}
	}
	if (v->s[v->i + 1] == '\0' && v->s[v->i] != ' ')
		k++;
	if (create_word(temp, v, &k, 1))
		return (MALLOC);
	return (0);
}

int	find_word(t_parser **temp, t_vars *v)
{
	check_quotes(v, v->s[v->i]);
	if (((v->s[v->i] == ' ' && v->oq) || (v->s[v->i + 1] == '\0'
				&& v->s[v->i] != ' ')))
	{
		if (v->nq && take_words_with_quotes(temp, v))
			return (MALLOC);
		else if (!v->nq && find_more_words(temp, v))
			return (MALLOC);
		v->nq = 0;
	}
	return (0);
}
