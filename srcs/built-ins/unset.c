/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:01 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/14 22:57:07 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

void static	env_find_rm(t_env **head, void *data_ref, int (*cmp)(char *,
			char *))
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if ((*cmp)(current->name, data_ref) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->name);
			free(current->value);
			free(current);
			current = NULL;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
int	ft_unset(t_min *tk, t_cmd *tmp)
{
	int	i;

	if (!tmp->args[1])
		return (0);
	else
	{
		i = 1;
		while (tmp->args[i])
		{
			if (env_find(tk->env, tmp->args[i], find_env))
				env_find_rm(&tk->env, tmp->args[i], find_env);
			i++;
		}
	}
	return (0);
}
