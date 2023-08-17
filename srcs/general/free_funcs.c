/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:47:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/17 13:15:36 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	free_double_int(char **old, int i)
{
	while (old[--i])
		free(old[i]);
	free(old);
	return (MALLOC);
}

char	**free_double_char(char **old, int i)
{
	while (old[--i])
		free(old[i]);
	free(old);
	return (NULL);
}

void	free_double_void(char **old)
{
	int	i;

	i = -1;
	if (!old)
		return ;
	while (old[++i])
		free(old[i]);
	free(old);
}

int	free_pointer(void *pt, int out)
{
	if (pt)
		free(pt);
	return (out);
}

void	free_err_f(char **line)
{
	free(*line);
	*line = NULL;
}
