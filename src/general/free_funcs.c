/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:47:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/07 13:55:21 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_double(char **dbl)
{
	int	i;

	i = 0;
//	printf("Pointer: %p\tValue: %s\tI: %d\n", dbl, dbl[0], i);
	while (dbl[i])
	{
//		printf("Value: %s\n", dbl[i]);
		free(dbl[i]);
		i++;
	}
	free(dbl);
//	*dbl = NULL;
}

int	free_tokens(t_minishell **tokens, int out)
{
	t_command	*tmp;
	t_command	*nxt;

	if ((*tokens)->command)
	{
		tmp = (*tokens)->command;
		nxt = (*tokens)->command->next;
		while (tmp)
		{
//			printf("CMD: %p\tNext: %p\tArgs: %p\n", tmp->cmd, tmp->next, tmp->args);
			free(tmp->cmd);
			printf("Cmd Args freed\n");
			free_double(tmp->args);
			free(tmp);
			tmp = nxt;
			if (tmp)
				nxt = tmp->next;
			else
				nxt = NULL;
		}
	}
	printf("Path freed\n");
	free_double((*tokens)->path);
	free((*tokens));
	*tokens = NULL;
	return (out);
}

