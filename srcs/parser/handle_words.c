/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:40:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/09/02 11:14:33 by vduchi           ###   ########.fr       */
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

int	add_or_join(t_parser **word_lst, t_vars *v, char *word, int mode)
{
	if (!mode)
	{
		if ((v->stp == 0 || v->s[v->stp - 1] == ' ') && add_word(word_lst,
				word))
			return (MALLOC);
		else if (v->stp > 0 && (v->s[v->stp - 1] != ' ') && join_words(word_lst,
				word))
			return (MALLOC);
	}
	else
	{
		if ((v->stp == 0 || v->s[v->stp - 1] == ' ' || v->s[v->stp - 1] == '<'
				|| v->s[v->stp - 1] == '>' || v->s[v->stp - 1] == '|')
			&& add_word(word_lst, word))
			return (MALLOC);
		else if (v->stp > 0 && v->s[v->stp - 1] != ' ' && v->s[v->stp
			- 1] != '<' && v->s[v->stp - 1] != '>' && v->s[v->stp - 1] != '|'
			&& join_words(word_lst, word))
			return (MALLOC);
	}
	return (0);
}

int static	word_control(t_parser **word_lst, t_vars *v, char *word, int mode)
{
	if (!mode && add_word(word_lst, word))
		return (MALLOC);
	else if (mode && (*word_lst)->word && (!ft_strncmp((*word_lst)->word, "<",
				2) || !ft_strncmp((*word_lst)->word, "<<", 3)
			|| !ft_strncmp((*word_lst)->word, ">", 2)
			|| !ft_strncmp((*word_lst)->word, ">>", 3)
			|| !ft_strncmp((*word_lst)->word, "|", 2)))
	{
		if (add_or_join(word_lst, v, word, 1))
			return (MALLOC);
	}
	else if (mode && add_or_join(word_lst, v, word, 0))
		return (MALLOC);
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
	if (!ft_strncmp(&v->s[v->stp], "\"\"", 3))
	{
		word = ft_strdup("");
		v->stp += 2;
	}
	else
		word = ft_substr(v->s, v->stp, len);
	if (word_control(word_lst, v, word, mode))
		return (MALLOC);
	v->stp += len;
	return (0);
}
