/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:50:22 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/22 20:16:50 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_access(char *to_free, char *str, int mode)
{
	if (to_free)
		free(to_free);
	if (mode == 1)
	{
		if (access(str, X_OK) == 0)
			return (0);
		if (access(str, F_OK) == 0)
			return (CMD_FOUND_NOT_EX);
		return (CMD_NOT_FOUND);
	}
	else if (mode == 2)
	{
		if (access(str, R_OK) == 0)
			return (0);
		if (access(str, F_OK) == 0)
			return (FILE_NOT_READ);
		return (FILE_NOT_FOUND);
	}
	if (access(str, F_OK) == 0 && access(str, W_OK) != 0)
		return (FILE_NOT_WRITE);
	return (0);
}

t_cmd	*set_new_command(int *number)
{
	t_cmd		*new;
	t_here_doc	*hdoc;

	new = ft_calloc(1, sizeof(t_cmd));
	hdoc = ft_calloc(1, sizeof(t_here_doc));
	if (!new || !hdoc)
	{
		if (new)
			free(new);
		return (NULL);
	}
	new->n = *number;
	new->out_fd = 1;
	new->hdoc = hdoc;
	(*number)++;
	return (new);
}

void	set_vars(t_vars *v, char *s)
{
	v->s = s;
	v->i = 0;
	v->sq = 0;
	v->dq = 0;
	v->oq = 1;
	// v->nq = 0;
	v->stp = 0;
	// v->count = 0;
}

t_cmd	*get_last_cmd(t_min **tk)
{
	t_cmd	*tmp;

	if (!(*tk)->cmds)
		return (NULL);
	tmp = (*tk)->cmds;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	end_refill(t_parser **word_lst, t_vars *v, t_word *w)
{
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
	w->word = NULL;
	w->k = 0;
	v->dq = 0;
	v->sq = 0;
	v->oq = 1;
	return (0);
}
