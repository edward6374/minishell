/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:50:22 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/15 18:10:22 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

void	check_quotes(t_vars *vars, char *c)
{
	if (*c == '\'' && vars->sin_qts == 0 && vars->dbl_qts == 0)
	{
		vars->sin_qts = 1;
		vars->num_qts++;
	}
	else if (*c == '\'' && vars->sin_qts == 1)
	{
		vars->sin_qts = 0;
		vars->num_qts++;
	}
	else if (*c == '\"' && vars->dbl_qts == 0 && vars->sin_qts == 0)
	{
		vars->dbl_qts = 1;
		vars->num_qts++;
	}
	else if (*c == '\"' && vars->dbl_qts == 1)
	{
		vars->dbl_qts = 0;
		vars->num_qts++;
	}
	if (vars->sin_qts == 0 && vars->dbl_qts == 0 \
		&& *c != '\'' && *c != '\"')
		vars->out_qts = 1;
	else
		vars->out_qts = 0;
//	printf("Char %c\tSingle: %d\tDouble: %d\tOut quotes: %d\tCount: %d\tStart point: %d\n", *c, \
//		vars->sin_qts, vars->dbl_qts, vars->out_qts, vars->num_qts, vars->start_point);
}

int	free_pointer(void *pt, int out)
{
	if (pt)
		free(pt);
	return (out);
}
