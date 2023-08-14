/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:47 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/14 22:00:51 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

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
