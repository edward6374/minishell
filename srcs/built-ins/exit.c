/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:49:21 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/21 16:59:44 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"
#include "minishell.h"

int	ft_exit(t_cmd *temp)
{
	int	i;
	int	value;

	i = -1;
	printf("exit\n");
	if (!temp->args[1])
		exit(0);
	while (temp->args[1][++i])
	{
		if (!ft_isdigit(temp->args[1][i]))
		{
			printf("minishell: exit: %s: number argument required\n",
					temp->args[1]);
			// tk->exit_value = 255;
			g_exit = 255;
			return (0);
		}
	}
	if (temp->args[2])
	{
		printf("minishell: exit: too manyn arguments\n");
		// tk->exit_value = 1;
		g_exit = 1;
		return (0);
	}
	value = ft_atoi(temp->args[1]);
	// tk->exit_value = value;
	g_exit = value;
	exit(value);
	return (0);
}
