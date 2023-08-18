/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 17:46:37 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/18 11:02:10 by vduchi           ###   ########.fr       */
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

int	free_commands(t_cmd **first, int out)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = *first;
	next = (*first)->next;
	while (next)
	{
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			free_double_void(tmp->args);
		if (tmp->err_f)
			free(tmp->err_f);
		free(tmp);
		tmp = next;
		next = tmp->next;
	}
	if (tmp->cmd)
		free(tmp->cmd);
	if (tmp->args)
		free_double_void(tmp->args);
	if (tmp->err_f)
		free(tmp->err_f);
	*first = NULL;
	return (free_pointer(tmp, out));
}

int	free_all(t_min *tk, int out)
{
	printf("Free all commands\n");
	if (tk->cmds)
		free_commands(&tk->cmds, 0);
	printf("Free all env\n");
	if (tk->env)
		free_env(tk->env);
	printf("Free all path\n");
	free(tk);
	return (out);
}
