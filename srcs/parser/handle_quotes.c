/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:01:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/12 17:31:07 by vduchi           ###   ########.fr       */
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
	int		l;
	int		k;
	int		sq;
	int		dq;
	char	*word;

	l = -1;
	sq = 0;
	dq = 0;
	k = v->stp - 1;
	if (!count)
		return (0);
	word = (char *)malloc(sizeof(char) * (count + 1));
	if (!word)
		return (MALLOC);
	while (++k <= v->i)
	{
		quotes_loop(v->s[k], &sq, &dq);
		if ((v->s[k] != '\'' && v->s[k] != '\"')
			|| (v->s[k] == '\'' && dq && !sq) || (v->s[k] == '\"' && !dq && sq))
		{
			word[++l] = v->s[k];
			printf("Last char: %c\tWord char: %c\n", word[l], v->s[k]);
		}
	}
	word[++l] = '\0';
	v->stp = k;
	if (add_word(temp, word))
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
	printf("I char: %c\n", v->s[i]);
	while (++k < i)
	{
		quotes_loop(v->s[k], &sq, &dq);
		if ((v->s[k] != '\'' && v->s[k] != '\"')
			|| (v->s[k] == '\'' && dq && !sq) || (v->s[k] == '\"' && !dq && sq))
		{
			word[++l] = v->s[k];
			printf("New char: %c\n", word[l]);
		}
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
	printf("Count: %d\tSq: %d\tDq: %d\n", count, sq, dq);
	while (++i <= v->i)
	{
		quotes_loop(v->s[i], &sq, &dq);
		printf("Char: %c\tSq: %d\tDq: %d\n", v->s[i], sq, dq);
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
	printf("While end\n");
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
