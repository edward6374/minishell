/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:46:37 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/29 19:05:14 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	free_env(t_env **first)
{
	t_env	*next;

	next = (*first)->next;
	while (next)
	{
		free((*first)->name);
		free((*first)->value);
		free((*first));
		(*first) = next;
		next = (*first)->next;
	}
	if ((*first)->name)
		free((*first)->name);
	if ((*first)->value)
		free((*first)->value);
	free((*first));
	*first = NULL;
	return (MALLOC);
}

void	free_commands(t_cmd **first)
{
	t_cmd	*next;

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

int	free_tokens(t_min **tk, t_parser **temp, int out)
{
	t_parser	*mov;
	t_parser	*after;

	if ((*tk)->cmds)
		free_commands(&(*tk)->cmds);
	if ((*tk)->env)
		free_env(&(*tk)->env);
	free_double_void((*tk)->path);
	free((*tk));
	*tk = NULL;
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

