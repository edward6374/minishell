/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:47:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/16 13:46:20 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_minishell	*free_struct(t_minishell **tokens)
{
	free_double_void((*tokens)->path);
	free_double_void((*tokens)->env);
	free(*tokens);
	*tokens = NULL;
	return (NULL);
}

int	free_double_int(char **old, int i)
{
	while (old[--i])
		free(old[i]);
	free(old);
	return (1);
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
