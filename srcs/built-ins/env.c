/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:47 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/14 10:57:18 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int ft_env(t_min *tk, t_cmd *tmp, int p)
{
	(void)tmp;
//	(void)p;

	t_env *env;

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
	//=======VALERIO==========================================================
	// t_env *loop;

	// loop = tk->env;
	// if (tmp->args[1])
	// {
	// 	printf("env: %s: %s\n", tmp->args[1], g_error_array[12]);
	// 	tk->exit_value = 127;
	// 	return (0);
	// }
	// while (loop)
	// {
	// 	if (loop->value && tmp->out_fd != 1)
	// 	{
	// 		ft_putstr_fd(loop->name, p);
	// 		ft_putstr_fd(loop->value, p);
	// 	}
	// 	else if (loop->value && tmp->out_fd == 1)
	// 		printf("%s%s\n", loop->name, loop->value);
	// 	loop = loop->next;
	// }

	return (0);
}
