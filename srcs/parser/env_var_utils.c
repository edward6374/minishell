/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:44:25 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/24 11:55:03 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "parser.h"

t_env	*search_env(t_env *env, void *data_ref, int (*cmp)(char *, char *, int))
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if ((*cmp)(curr->name, data_ref, 0) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	add_env_var(t_word *w, t_env **env)
{
	int		i;
	t_env	*next;

	i = -1;
	while ((*env)->value[++i])
		w->word[++w->l] = (*env)->value[i];
	w->i += ft_strlen((*env)->name);
	next = (*env)->next;
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = next;
	if (*env)
		(*env)->before = NULL;
	return (0);
}
