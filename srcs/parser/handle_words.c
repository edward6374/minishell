/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:40:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/21 10:22:07 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "built-ins.h"

int	join_words(t_parser **word_lst, char *word)
{
	char	*new_word;

	printf("Join words: --%s--\t--%s--\n", (*word_lst)->word, word);
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

	printf("Add word: --%s--\n", word);
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

t_env	*new_list_elem(t_env *found, t_env **old_tmp, t_vars *v, int *i)
{
	int		count;
	t_env	*new;

	count = *i + 1;
	while ((v->s[count] >= 'a' && v->s[count] <= 'z')
		|| (v->s[count] >= 'A' && v->s[count] <= 'Z')
		|| (v->s[count] >= '0' && v->s[count] <= '9'))
		count++;
	*i = count - 1;
	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_strdup(found->name);
	new->value = ft_strdup(found->value);
	if (old_tmp)
	{
		(*old_tmp)->next = new;
		new->before = *old_tmp;
	}
	return (new);
}

t_env	*find_env_vars(t_env *env, t_vars *v)
{
	int		i;
	t_env	*tmp;
	t_env	*found;
	t_env	*env_list;

	env_list = NULL;
	i = v->stp - 1;
	while (++i < v->i)
	{
		check_quotes(v, &v->s[i]);
		if ((v->oq || v->dq) && v->s[i] == '$')
		{
			found = env_find(env, &v->s[i + 1], find_env);
			if (found && !env_list)
			{
				env_list = new_list_elem(found, NULL, v, &i);
				tmp = env_list;
			}
			else if (found)
				tmp = new_list_elem(found, &tmp, v, &i);
		}
	}
//	print_list(env_list);
	return (env_list);
}

int	create_word(t_parser **word_lst, t_vars *v, int *i, int mode)
{
	int		len;
	char	*word;

	if (!mode)
	{
		len = 1;
		if (((v->s[*i] == '<' && v->s[*i + 1] == '<')
			|| (v->s[*i] == '>' && v->s[*i + 1] == '>')) && (*i)++)
			len++;
	}
	else
		len = *i - v->stp;
	printf("Mode: %d\tBefore start: %d\tchar: --%c--\n", mode, v->stp, v->s[v->stp]);
	word = ft_substr(v->s, v->stp, len);
	printf("Word: --%s--\n",  word);
	if (!mode && add_word(word_lst, word))
		return (MALLOC);
	else if (mode && (v->stp > 0 && (v->s[v->stp - 1] == '\''
		|| v->s[v->stp - 1] == '\"') && join_words(word_lst, word)))
		return (MALLOC);
	else if (mode && (v->stp == 0 || (v->s[v->stp - 1] != '\''
		&& v->s[v->stp - 1] != '\"')) && add_word(word_lst, word))
		return (MALLOC);
	v->stp += len;
	return (0);
}

int	multiple_words(t_parser **word_lst, t_vars *v, int end)
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
	}
	if (i - v->stp > 0 && create_word(word_lst, v, &i, 1))
		return (MALLOC);
	return (0);
}

int	refill_word(t_parser **word_lst, t_vars *v, t_word *w, int mode)
{
	char	c;

	if (mode)
		c = '\"';
	else
		c = '\'';
	w->word = (char *)malloc(sizeof(char) * (w->count + 1));
	if (!w->word)
		return (MALLOC);
	w->i = *w->idx + 1;
	while (v->s[w->i] != c)
		w->word[++w->l] = v->s[w->i++];
	w->word[++w->l] = '\0';
	printf("Refill words: --%s--\n", w->word);
	if ((v->stp == 0 || v->s[*w->idx - 1] == ' ' || v->s[*w->idx - 1] == '<'
		|| v->s[*w->idx - 1] == '>' || v->s[*w->idx - 1] == '|')
		&& add_word(word_lst, w->word))
		return (MALLOC);
	else if (v->stp > 0 && v->s[*w->idx - 1] != ' ' && v->s[*w->idx - 1] != '<'
		&& v->s[*w->idx - 1] != '>' && v->s[*w->idx - 1] != '|'
		&& join_words(word_lst, w->word))
		return (MALLOC);
	*w->idx = w->i;
	v->stp = w->i + 1;
	v->dq = 0;
	v->sq = 0;
	v->oq = 1;
	return (0);
}

int	words_dbl_qts(t_parser **word_lst, t_vars *v, t_env *env_list, int *idx)
{
	t_word	w;
	t_env	*tmp;

	w.l = -1;
	w.i = *idx;
	w.idx = idx;
	w.count = 0;
	tmp = env_list;
	if (v->s[*idx] == '\"' && v->s[*idx + 1] == '\"' && v->oq++ && v->dq--)
		return (0);
	while (v->s[++w.i] != '\"')
	{
		if (v->s[w.i] == '$' && !ft_strncmp(tmp->name, &v->s[w.i],
			ft_strlen(tmp->name) - 1))
		{
			w.count += ft_strlen(tmp->value);
			tmp = tmp->next;
		}
		else
			w.count++;
	}
	return (refill_word(word_lst, v, &w, 1));
}

int	words_sin_qts(t_parser **word_lst, t_vars *v, int *idx)
{
	t_word	w;

	w.l = -1;
	w.i = *idx;
	w.idx = idx;
	w.count = 0;
	printf("Single quotes\n");
	if (v->s[*idx] == '\'' && v->s[*idx + 1] == '\"' && v->oq++ && v->sq--)
		return (0);
	while (v->s[++w.i] != '\'')
		w.count++;
	return (refill_word(word_lst, v, &w, 0));
}

int	find_words(t_env *env_vars, t_parser **tmp, t_vars *v)
{
	int		i;
	t_env	*env_list;

	i = v->stp - 1;
	env_list = find_env_vars(env_vars, v);
	while (++i < v->i)
	{
		printf("Loop char: --%c--\n", v->s[i]);
		check_quotes(v, &v->s[i]);
		if (v->oq && ((v->s[i + 1] == '\'' || v->s[i + 1] == '\"')
			|| (v->s[i + 1] == '\0' && v->s[i] != ' ') || v->s[i + 1] == ' ')
			&& multiple_words(tmp, v, i + 1))
			return (MALLOC);
		else if (v->sq && words_sin_qts(tmp, v, &i))
			return (MALLOC);
		else if (v->dq && words_dbl_qts(tmp, v, env_list, &i))
			return (MALLOC);
	}
	printf("End loop: Char i: --%c--\tI: %d\tStart: %d\tChar idx: --%c--\n", v->s[i], i, v->stp, v->s[v->stp]);
	if ((v->s[v->i] == ' ' && v->s[v->i - 1] != ' ')
		|| (v->s[v->i] == '\0' && v->s[v->i - 1] != ' '))
		if (i - v->stp > 0 && create_word(tmp, v, &i, 1))
			return (MALLOC);
	return (0);
}
