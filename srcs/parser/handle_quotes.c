/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:01:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 14:49:55 by nmota-bu         ###   ########.fr       */
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

int	last_word_quotes(t_parser **temp, t_vars *v, int count)
{
	t_lastword	data;

	data.l = -1;
	data.sq = 0;
	data.dq = 0;
	data.k = v->stp - 1;
	if (!count)
		return (0);
	data.word = (char *)malloc(sizeof(char) * (count + 1));
	if (!data.word)
		return (MALLOC);
	while (++data.k <= v->i)
	{
		quotes_loop(v->s[data.k], &data.sq, &data.dq);
		if ((v->s[data.k] != '\'' && v->s[data.k] != '\"')
			|| (v->s[data.k] == '\'' && data.dq && !data.sq)
			|| (v->s[data.k] == '\"' && !data.dq && data.sq))
			data.word[++data.l] = v->s[data.k];
	}
	data.word[++data.l] = '\0';
	v->stp = data.k;
	if (add_word(temp, data.word))
		return (MALLOC);
	return (0);
}

int	add_word_quotes(t_parser **temp, t_vars *v, char *word, int i)
{
	int	l;
	int	k;
	int	sq;
	int	dq;

	l = -1;
	sq = 0;
	dq = 0;
	k = v->stp - 1;
	while (++k < i)
	{
		quotes_loop(v->s[k], &sq, &dq);
		if ((v->s[k] != '\'' && v->s[k] != '\"') || (v->s[k] == '\'' && dq
				&& !sq) || (v->s[k] == '\"' && !dq && sq))
			word[++l] = v->s[k];
	}
	if (v->s[i] != '<' && v->s[i] != '>' && v->s[i] != '|')
		word[++l] = v->s[++k];
	word[++l] = '\0';
	v->stp = k;
	if (add_word(temp, word) || ((v->s[i] == '<' || v->s[i] == '>'
				|| v->s[i] == '|') && create_word(temp, v, &i, 0)))
		return (MALLOC);
	return (0);
}

int	take_words_with_quotes(t_parser **temp, t_vars *v)
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
	while (++i <= v->i)
	{
		quotes_loop(v->s[i], &sq, &dq);
		if ((v->s[i] == '<' || v->s[i] == '>' || v->s[i] == '|') && !dq && !sq)
		{
			word = (char *)malloc(sizeof(char) * (count + 1));
			if (!word || add_word_quotes(temp, v, word, i))
				return (MALLOC);
			count = 0;
		}
		else
			count++;
	}
	return (last_word_quotes(temp, v, count));
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
