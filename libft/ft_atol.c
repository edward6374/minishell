/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:22:49 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/24 14:14:17 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdio.h>

long long int	ft_atol(const char *str)
{
	int				sign;
	long long int	res;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\f'
		|| *str == '\n' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (res > ((LONG_MAX - '0') / 10))
			return (0);
		res = (res * 10) + (*str - '0');
		str++;
	}
	if (*str != '\0' && *str != ' ')
		return (0);
	res = res * sign;
	return (res);
}
