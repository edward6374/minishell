/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:47 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 16:36:32 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	find_env(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (1);
	}
	if (s1[i] == '=')
		return (0);
	return (1);
}

t_env	*env_find(t_env *env, void *data_ref, int (*cmp)(char *, char *))
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if ((*cmp)(curr->name, data_ref) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	ft_env(t_min *tk, t_cmd *tmp, int p)
{
	t_env	*env;

	env = tk->env;
	while (env != NULL)
	{
		if (env->value)
		{
			if (tmp->next)
			{
				ft_putstr_fd(env->name, p);
				ft_putstr_fd(env->value, p);
				ft_putchar_fd('\n', p);
			}
			else
				printf("%s%s\n", env->name, env->value);
		}
		env = env->next;
	}
	return (0);
}
