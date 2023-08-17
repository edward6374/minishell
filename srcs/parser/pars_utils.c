/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:50:22 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/17 22:54:10 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

int	check_access(char *str, int mode)
{
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
	if (access(str, W_OK) == 0)
		return (0);
	if (access(str, F_OK) == 0)
		return (FILE_NOT_WRITE);
	return (FILE_NOT_FOUND);
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
	v->i = -1;
	v->count = -1;
	v->sq = 0;
	v->dq = 0;
	v->oq = 1;
	v->nq = 0;
	v->stp = 0;
	v->s = s;
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

void	check_quotes(t_vars *vars, char c)
{
	if (c == '\'' && vars->sq == 0 && vars->dq == 0)
	{
		vars->sq = 1;
		vars->nq++;
	}
	else if (c == '\'' && vars->sq == 1)
	{
		vars->sq = 0;
		vars->nq++;
	}
	else if (c == '\"' && vars->dq == 0 && vars->sq == 0)
	{
		vars->dq = 1;
		vars->nq++;
	}
	else if (c == '\"' && vars->dq == 1)
	{
		vars->dq = 0;
		vars->nq++;
	}
	if (vars->sq == 0 && vars->dq == 0 && c != '\'' && c != '\"')
		vars->oq = 1;
	else
		vars->oq = 0;
}
