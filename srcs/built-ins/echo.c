/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:32:30 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/28 20:45:59 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_echo(t_cmd *temp, int p)
{
	int	i;

	i = -1;
	while (temp->args[++i])
	{
		printf("%s", temp->args[i]);
		if (temp->args[i + 1])
			printf(" ");
	}
	printf("\n");
	return (0);
}
