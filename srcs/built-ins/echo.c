/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:32:30 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/18 17:50:57 by nmota-bu         ###   ########.fr       */
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

	i = 1;
	no_newline = is_n(args[1], &i);
	while (args[i] != NULL)
	{
		if (!ft_strncmp(args[i], "-n", 3) && no_newline)
		{
			i++;
			continue ;
		}
		if (tmp->next)
			print_echo(args, i, p, 0);
		// {
		// 	ft_putstr_fd(args[i], p);
		// 	if (args[i + 1])
		// 		ft_putchar_fd(' ', p);
		// }
		else
			print_echo(args, i, p, 1);
		// {
		// 	printf("%s", args[i]);
		// 	if (args[i + 1])
		// 		printf(" ");
		// }
		i++;
	}
	if (!no_newline && tmp->next)
		ft_putchar_fd('\n', p);
	else if (!no_newline && !tmp->next)
		printf("\n");
	return (0);
}
