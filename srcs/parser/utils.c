/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:50:22 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/06 17:15:40 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

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
	if (vars->sq == 0 && vars->dq == 0 \
		&& c != '\'' && c != '\"')
		vars->oq = 1;
	else
		vars->oq = 0;
//	printf("Char %c\tSingle: %d\tDouble: %d\tOut quotes: %d\tCount: %d\tStart point: %d\n", c, \
//		vars->sq, vars->dq, vars->oq, vars->nq, vars->stp);
}

int	free_pointer(void *pt, int out)
{
	if (pt)
		free(pt);
	return (out);
}
