/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:46:37 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 16:40:10 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			free_double_void(tmp->args);
		free(tmp);
		tmp = next;
		next = tmp->next;
	}
	if (tmp->cmd)
		free(tmp->cmd);
	if (tmp->args)
		free_double_void(tmp->args);
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
