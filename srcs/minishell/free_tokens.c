/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:46:37 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/15 18:14:02 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_commands(t_command **first)
{
	t_command	*next;

	next = (*first)->next;
	while (next)
	{
		free((*first)->cmd);
		free_double_void((*first)->args);
		free((*first));
		(*first) = next;
		next = (*first)->next;
	}
	free((*first)->cmd);
	free_double_void((*first)->args);
	free((*first));
	*first = NULL;
}

int	free_tokens(t_minishell **tokens, t_parser **temp, int out)
{
	t_parser	*mov;
	t_parser	*after;

	if ((*tokens)->command)
		free_commands(&(*tokens)->command);
	free_double_void((*tokens)->path);
	free_double_void((*tokens)->env);
	free((*tokens));
	*tokens = NULL;
	if (temp && *temp)
	{
		mov = *temp;
		after = (*temp)->next;
		while (after)
		{
			free(mov->word);
			free(mov);
			mov = after;
			after = mov->next;
		}
		free(mov->word);
		free(mov);
	}
	*temp = NULL;
	return (out);
}

