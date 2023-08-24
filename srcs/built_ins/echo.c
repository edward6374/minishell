/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:32:30 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/24 15:37:03 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
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

void	print_echo(char *str)
{
	if (!ft_strncmp(str, "> ", 3) || !ft_strncmp(str, ">> ", 4)
		|| !ft_strncmp(str, "< ", 3) || !ft_strncmp(str, "<< ", 4)
		|| !ft_strncmp(str, "| ", 3))
		str[ft_strlen(str) - 1] = '\0';
	printf("%s", str);
}

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
		print_echo(args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
