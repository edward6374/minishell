/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:47 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/26 18:03:06 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_env(t_min *tk, t_cmd *temp)
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
		if (!ft_strchr(loop->str, '='))
		{
			loop = loop->next;
			continue ;
		}
		printf("%s\n", loop->str);
		loop = loop->next;
	}
	return (0);
}
