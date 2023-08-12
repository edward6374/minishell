/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:47:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/12 17:45:18 by vduchi           ###   ########.fr       */
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
	{
//		printf("\nPointer: %p\n", old[i]);
//		printf("Element: %s\n", old[i]);
		free(old[i]);
//		printf("Free element\n\n");
	}
//	printf("Array\n");
	free(old);
//	printf("Free array\n");
}

int	free_pointer(void *pt, int out)
{
	printf("Free single pointer\n");
	if (pt)
		free(pt);
	return (out);
}
