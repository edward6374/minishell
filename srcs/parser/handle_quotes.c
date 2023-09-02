/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:01:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/09/02 11:54:33 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int static	refill_word(t_parser **word_lst, t_vars *v, t_word *w, t_env **env)
{
	char	c;

	if (w->check)
		c = '\"';
	else
		c = '\'';
	w->word = (char *)malloc(sizeof(char) * (w->count + 1));
	if (!w->word)
		return (MALLOC);
	w->i = *w->idx + 1;
	while (v->s[w->i] != c && v->s[w->i] != '\0')
	{
		if (w->check && v->s[w->i] == '$' && *env && !ft_strncmp(&v->s[w->i
				+ 1], (*env)->name, ft_strlen((*env)->name) - 1))
			add_env_var(w, env);
		else
			w->word[++w->l] = v->s[w->i++];
	}
	w->word[++w->l] = '\0';
	if (end_refill(word_lst, v, w))
		return (MALLOC);
	return (0);
}

int	words_dbl_qts(t_parser **word_lst, t_vars *v, t_env **env, int *idx)
{
	t_word	w;
	t_env	*tmp;

	w.check = 1;
	w.l = -1;
	w.i = *idx;
	w.idx = idx;
	w.count = 0;
	tmp = *env;
	if (v->s[*idx] == '\"' && v->s[*idx + 1] == '\"' && v->s[*idx + 2] == ' ')
		return (create_word(word_lst, v, idx, 0));
	while (v->s[++w.i] != '\"')
	{
		if (v->s[w.i] == '$' && tmp && !ft_strncmp(tmp->name, &v->s[w.i + 1],
				ft_strlen(tmp->name) - 1))
		{
			w.count += ft_strlen(tmp->value);
			tmp = tmp->next;
		}
		else
			w.count++;
	}
	return (refill_word(word_lst, v, &w, env));
}

int	words_sin_qts(t_parser **word_lst, t_vars *v, t_env **env, int *idx)
{
	t_word	w;

	w.check = 0;
	w.l = -1;
	w.i = *idx;
	w.idx = idx;
	w.count = 0;
	if (v->s[*idx] == '\'' && v->s[*idx + 1] == '\'' && v->oq++ && v->sq--)
		return (0);
	while (v->s[++w.i] != '\'')
		w.count++;
	return (refill_word(word_lst, v, &w, env));
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

void	check_quotes(t_vars *vars, char *c)
{
	if (*c == '\'' && vars->sq == 0 && vars->dq == 0)
		vars->sq = 1;
	else if (*c == '\'' && vars->sq == 1)
		vars->sq = 0;
	else if (*c == '\"' && vars->dq == 0 && vars->sq == 0)
		vars->dq = 1;
	else if (*c == '\"' && vars->dq == 1)
		vars->dq = 0;
	if (vars->sq == 0 && vars->dq == 0 && (*c != '\'' || *c != '\"'))
		vars->oq = 1;
	else
		vars->oq = 0;
}
