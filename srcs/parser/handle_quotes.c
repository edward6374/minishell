/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:01:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/18 03:22:24 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	quotes_loop(char c, int *sq, int *dq)
{
	if (c == '\"' && !*dq && !*sq)
		(*dq)++;
	else if (c == '\'' && !*dq && !*sq)
		(*sq)++;
	else if (c == '\"' && *dq && !*sq)
		(*dq)--;
	else if (c == '\'' && !*dq && *sq)
		(*sq)--;
}

int	last_word_quotes(t_parser **word_lst, t_vars *v, int count)
{
	t_word	data;

	data.l = -1;
	data.sq = 0;
	data.dq = 0;
	data.k = v->stp - 1;
	if (!count)
		return (0);
	data.word = (char *)malloc(sizeof(char) * (count + 1));
	if (!data.word)
		return (MALLOC);
	while (++data.k < v->i)
	{
		quotes_loop(v->s[data.k], &data.sq, &data.dq);
		if ((v->s[data.k] != '\'' && v->s[data.k] != '\"')
			|| (v->s[data.k] == '\'' && data.dq && !data.sq)
			|| (v->s[data.k] == '\"' && !data.dq && data.sq))
			data.word[++data.l] = v->s[data.k];
	}
//	printf("Char k: %c\tK: %c\tChar l: %d\n", v->s[v->i - 1], v->s[data.k - 1], data.l);
	data.word[++data.l] = '\0';
	v->stp = data.k;
//	printf("Word: --%s--\n", data.word);
	if (add_word(word_lst, data.word))
		return (MALLOC);
	return (0);
}

int	add_word_quotes(t_parser **word_lst, t_vars *v, char *word, int i)
{
	t_word	data;

	data.l = -1;
	data.sq = 0;
	data.dq = 0;
	data.k = v->stp - 1;
	while (++data.k < i)
	{
		quotes_loop(v->s[data.k], &data.sq, &data.dq);
		if ((v->s[data.k] != '\'' && v->s[data.k] != '\"')
			|| (v->s[data.k] == '\'' && data.dq && !data.sq)
			|| (v->s[data.k] == '\"' && !data.dq && data.sq))
			word[++data.l] = v->s[data.k];
	}
	if (v->s[i] != '<' && v->s[i] != '>' && v->s[i] != '|')
		word[++data.l] = v->s[++data.k];
	word[++data.l] = '\0';
	v->stp = data.k;
//	printf("Word: %s\n", word);
	if (add_word(word_lst, word) || ((v->s[i] == '<' || v->s[i] == '>'
				|| v->s[i] == '|') && create_word(word_lst, v, &i, 0)))
		return (MALLOC);
	return (0);
}

int	take_words_with_quotes(t_parser **word_lst, t_vars *v)
{
	int		i;
	int		sq;
	int		dq;
	int		count;
	char	*word;

	sq = 0;
	dq = 0;
	count = 0;
	i = v->stp - 1;
//	printf("I: %d\tv->i: %d\n", i, v->i);
	while (++i <= v->i)
	{
		quotes_loop(v->s[i], &sq, &dq);
		if ((v->s[i] == '<' || v->s[i] == '>' || v->s[i] == '|') && !dq && !sq)
		{
			word = (char *)malloc(sizeof(char) * (count + 1));
			if (!word || add_word_quotes(word_lst, v, word, i))
				return (MALLOC);
			count = 0;
		}
		else if (i != v->stp && i != v->i)
			count++;
	}
//	printf("Count: %d\n", count);
	return (last_word_quotes(word_lst, v, count));
}

int	count_quotes(char *string)
{
	int	i;
	int	sq;
	int	dq;

	i = -1;
	sq = 0;
	dq = 0;
	while (string[++i])
	{
		if (string[i] == '\'' && !sq && !dq)
			sq++;
		else if (string[i] == '\"' && !sq && !dq)
			dq++;
		else if (string[i] == '\'' && sq && !dq)
			sq--;
		else if (string[i] == '\"' && !sq && dq)
			dq--;
	}
	if (!dq && !sq)
		return (0);
	return (1);
}
