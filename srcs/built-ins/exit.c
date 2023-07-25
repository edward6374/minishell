/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:03:37 by vduchi            #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_exit(t_min *tk, t_cmd *temp)
{
	int	i;
	int	value;

	i = -1;
	printf("exit\n");
//	write(1, "\rexit", 5);
//	rl_replace_line("exit", 0);
//	rl_on_new_line();
//	rl_redisplay();
	if (!temp->args[1])
		exit(0);
	while (temp->args[1][++i])
		if (!ft_isdigit(temp->args[1][i]))
			exit_error(g_error_array[13], 1);
	value = ft_atoi(temp->args[1]);
	tk->exit_value = value;
	if (temp->args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (0);
	}
	exit(value);
	return (0);
}
