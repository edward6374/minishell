/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:32:30 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/17 13:52:38 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

char	*take_dollar(char *env)
{
	if (*env == '$')
		env++;
	return (env);
}

void	print_echo(t_env *env, char *args)
{
	t_env	*find;

	find = env_find(env, take_dollar(args), find_env);
	printf("%s", find->value);
}

int	is_n(char *args, int *i)
{
	if (args != NULL && ft_strncmp(args, "-n", 2) == 0)
	{
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

int	ft_echo(t_cmd *tmp, char **args, int p)
{
	int	i;
	int	no_newline;

	i = 0;
	no_newline = is_n(args[1], &i);
	while (args[++i] != NULL)
	{
		if (tmp->next)
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
	if (!no_newline && tmp->next)
		ft_putchar_fd('\n', p);
	else if (!no_newline && !tmp->next)
		printf("\n");
	return (0);
}
