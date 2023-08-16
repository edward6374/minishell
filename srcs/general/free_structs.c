/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:46:37 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 13:21:22 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO
// cambiar nombre y mover las funciones dondes corresponda

int	free_parser(t_parser *words, int out)
{
	t_parser	*tmp;
	t_parser	*next;

	tmp = words;
	next = words->next;
	while (next)
	{
		free(tmp->word);
		free(tmp);
		tmp = next;
		next = tmp->next;
	}
	free(tmp->word);
	free(tmp);
	return (out);
}

int	free_env(t_env *first)
{
	t_env	*next;

	printf("Free env\n");
	next = first->next;
	while (next)
	{
		free(first->name);
		free(first->value);
		free(first);
		first = next;
		next = first->next;
	}
	if (first->name)
		free(first->name);
	if (first->value)
		free(first->value);
	free(first);
	return (MALLOC);
}

void	free_commands(t_cmd **first)
{
	t_cmd	*tmp;
	t_cmd	*next;

	printf("Free commands\n");
	tmp = *first;
	next = (*first)->next;
	while (next)
	{
		//		printf("Free while start\n\n");
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			free_double_void(tmp->args);
		free(tmp);
		tmp = next;
		next = tmp->next;
		//		printf("Free while end\n\n");
	}
	//	printf("While commands finished\n");
	if (tmp->cmd)
		free(tmp->cmd);
	//	printf("Free last command\n");
	if (tmp->args)
		free_double_void(tmp->args);
	//	printf("Free double void\n");
	free(tmp);
	*first = NULL;
}

int	free_all(t_min *tk, int out)
{
	printf("Free tokens\n");
	if (tk->cmds)
		free_commands(&tk->cmds);
	if (tk->env)
		free_env(tk->env);
	free_double_void(tk->path);
	tk->path = NULL;
	free(tk);
	return (out);
}
