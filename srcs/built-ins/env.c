/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:47 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/25 20:36:49 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_env(t_min *tk, t_cmd *temp)
{
	int	i;

	i = -1;
	if (temp->args[1])
	{
		printf("env: %s: %s\n", temp->args[1], g_error_array[12]);
		tk->exit_value = 127;
		return (0);
	}
	while (tk->env_vars[++i])
	{
		if (!ft_strchr(tk->env_vars[i], '='))
			continue ;
		printf("%s\n", tk->env_vars[i]);
	}
	return (0);
}
