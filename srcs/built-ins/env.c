/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:47 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/29 19:44:19 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_env(t_min *tk, t_cmd *temp, int p)
{
	t_env	*loop;

	loop = tk->env;
	if (temp->args[1])
	{
		printf("env: %s: %s\n", temp->args[1], g_error_array[12]);
		tk->exit_value = 127;
		return (0);
	}
	while (loop)
	{
		if (loop->value && temp->out != 1)
		{
			ft_putstr_fd(loop->name, p);
			ft_putstr_fd(loop->value, p);
		}
		else if (loop->value && temp->out == 1)
			printf("%s%s\n", loop->name, loop->value);
		loop = loop->next;
	}
	return (0);
}
