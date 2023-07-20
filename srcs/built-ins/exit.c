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

int	ft_exit(int value)
{
	printf("exit\n");
//	write(1, "\rexit", 5);
//	rl_replace_line("exit", 0);
//	rl_on_new_line();
//	rl_redisplay();
	exit(value);
	return (0);
}
