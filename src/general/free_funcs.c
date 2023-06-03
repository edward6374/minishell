/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:47:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/03 19:11:35 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_double(char ***dbl)
{
	int	i;

	i = -1;
	while ((*dbl)[++i])
		free((*dbl)[i]);
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
			free_double(&tmp->args);
			free(tmp);
			tmp = nxt;
			nxt = tmp->next;
		}
	}
	free_double(&(*tokens)->path);
	free((*tokens));
	*tokens = NULL;
}

