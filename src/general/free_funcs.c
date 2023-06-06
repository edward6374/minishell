/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:47:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/06 20:13:01 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_double(char ***dbl)
{
	int	i;

	i = 0;
	printf("Pointer: %p\tValue: %s\tI: %d\n", *dbl, *dbl[0], i);
	while (*dbl[i])
	{
		free(*dbl[i]);
		printf("After\n");
		i++;
	}
	free(*dbl);
	*dbl = NULL;
}

void	free_tokens(t_minishell **tokens)
{
	t_command	*tmp;
	t_command	*nxt;

//	free((*tokens)->command->cmd);
//	free_double(&(*tokens)->command->args);
//	free((*tokens)->command);
	if ((*tokens)->command)
	{
		tmp = (*tokens)->command;
		nxt = (*tokens)->command->next;
		while (tmp)
		{
			free(tmp->cmd);
			printf("CMD: %p\tNext: %p\nArgs: %p\n", tmp->cmd, tmp->next, tmp->args);
			free_double(&tmp->args);
			free(tmp);
			tmp = nxt;
			if (tmp)
				nxt = tmp->next;
			else
				nxt = NULL;
		}
	}
	free_double(&(*tokens)->path);
	free((*tokens));
	*tokens = NULL;
}

