/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:40:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/24 15:37:09 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	join_words(t_parser **word_lst, char *word)
{
	char	*new_word;

	new_word = ft_strjoin((*word_lst)->word, word);
	if (!new_word)
		return (MALLOC);
	free((*word_lst)->word);
	(*word_lst)->word = new_word;
	return (0);
}

int	add_word(t_parser **word_lst, char *word)
{
	t_parser	*new;

	if (!(*word_lst)->word)
		(*word_lst)->word = word;
	else
	{
		new = (t_parser *)malloc(sizeof(t_parser));
		if (!new)
			return (free_pointer(word, MALLOC));
		new->word = word;
		new->next = NULL;
		new->before = (*word_lst);
		(*word_lst)->next = new;
		(*word_lst) = (*word_lst)->next;
		new = NULL;
	}
	return (0);
}

int	create_word(t_parser **word_lst, t_vars *v, int *i, int mode)
{
	int		len;
	char	*word;

	if (!mode)
	{
		len = 1;
		if (((v->s[*i] == '<' && v->s[*i + 1] == '<') || (v->s[*i] == '>'
					&& v->s[*i + 1] == '>')) && (*i)++)
			len++;
	}
	else
		len = *i - v->stp;
	word = ft_substr(v->s, v->stp, len);
	if (!mode && add_word(word_lst, word))
		return (MALLOC);
	else if (mode && (v->stp > 0 && (v->s[v->stp - 1] != ' ')
			&& join_words(word_lst, word)))
		return (MALLOC);
	else if (mode && (v->stp == 0 || v->s[v->stp - 1] == ' ')
		&& add_word(word_lst, word))
		return (MALLOC);
	v->stp += len;
	return (0);
}

int	multiple_words(t_parser **word_lst, t_env **env, t_vars *v, int end)
{
	int	i;

	i = v->stp - 1;
	while (++i < end)
	{
		if (v->s[i] == '<' || v->s[i] == '>' || v->s[i] == '|')
		{
			if (i - v->stp > 0 && create_word(word_lst, v, &i, 1))
				return (MALLOC);
			if (create_word(word_lst, v, &i, 0))
				return (MALLOC);
		}
		else if (v->s[i] == '$' && check_env_word(word_lst, env, v, &i))
			return (MALLOC);
	}
	if (i - v->stp > 0 && create_word(word_lst, v, &i, 1))
		return (MALLOC);
	return (0);
}

int	refill_word(t_parser **word_lst, t_vars *v, t_word *w, t_env **env)
{
	char	c;

	if (w->k)
		c = '\"';
	else
		c = '\'';
	w->word = (char *)malloc(sizeof(char) * (w->count + 1));
	if (!w->word)
		return (MALLOC);
	w->i = *w->idx + 1;
	while (v->s[w->i] != c && v->s[w->i] != '\0')
	{
		if (w->k && v->s[w->i] == '$' && *env && !ft_strncmp(&v->s[w->i + 1],
				(*env)->name, ft_strlen((*env)->name) - 1))
			add_env_var(w, env);
		else
			w->word[++w->l] = v->s[w->i++];
	}
	w->word[++w->l] = '\0';
	if (end_refill(word_lst, v, w))
		return (MALLOC);
	return (0);
}
