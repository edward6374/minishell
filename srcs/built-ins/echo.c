/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:32:30 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/11 14:21:15 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int ft_echo(t_cmd *tmp, int p)
{
	(void)tmp;
	(void)p;

	printf("%s\n", tmp->args[1]);
	// int	i;

	// i = -1;
	// while (temp->args[++i])
	// {
	// 	printf("%s", temp->args[i]);
	// 	if (temp->args[i + 1])
	// 		printf(" ");
	// }
	// printf("\n");
	return (0);
}
