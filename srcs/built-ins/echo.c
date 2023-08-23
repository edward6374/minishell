/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:32:30 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/23 18:13:24 by nmota-bu         ###   ########.fr       */
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

// int	ft_echo(char **args)
// {
// 	int	i;
// 	int	no_newline;

// 	i = 1;
// 	if (args[1])
// 		no_newline = is_n(args[1], &i);
// 	else
// 	{
// 		printf("\n");
// 		return (0);
// 	}
// 	while (args[i] != NULL)
// 	{
// 		if (!ft_strncmp(args[i], "-n", 3) && no_newline && i++)
// 			continue ;
// 		printf("%s", args[i]);
// 		if (args[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);
// }

int	ft_echo(char **args, int i)
{
	int	no_newline;

	if (args[1])
		no_newline = is_n(args[1], &i);
	else
	{
		printf("\n");
		return (0);
	}
	while (args[i] != NULL)
	{
		if (!ft_strncmp(args[i], "-n", 3) && no_newline)
		{
			i++;
			continue ;
		}
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
