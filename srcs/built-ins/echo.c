/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:32:30 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/23 13:56:01 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"
#include <stdbool.h>

int	is_n(char *args, int *i)
{
	int	j;

	j = 2;
	if (*i == 1 && args != NULL && !ft_strncmp(args, "-n", 2)
		&& args[2] == '\0')
	{
		(*i)++;
		return (TRUE);
	}
	else if (args[0] == '-' && args[1] == 'n')
	{
		while (args[j])
		{
			if (args[j] != 'n')
				return (FALSE);
			j++;
		}
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

void static	print_echo(char **args, int i, int p, int type)
{
	if (!type)
	{
		ft_putstr_fd(args[i], p);
		if (args[i + 1])
			ft_putchar_fd(' ', p);
	}
	else
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
	}
}

int	ft_echo(t_cmd *tmp, char **args, int p)
{
	int	i;
	int	no_newline;

	(void)p;
	(void)tmp;
	i = 1;
	if (args[1])
		no_newline = is_n(args[1], &i);
	else
	{
		printf("\n");
		return (0);
	}
	while (args[i] != NULL)
	{
		if (!ft_strncmp(args[i], "-n", 3) && no_newline && i++)
			continue;
		print_echo(args, i, p, 1);
		i++;
	}
	printf("\n");
	return (0);
}
