/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:51:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/09 13:54:10 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

int	check_name(char *str, char *var)
{
	int	i;

	i = 0;
	while (str[i] && var[i] && str[i] == var[i])
		i++;
	if (var[i] == '\0')
		return (0);
	return (1);
}

int	check_env_var(t_parser **temp, char *env[], char *str, int *i)
{
	int		k;
	int		end;
	char	*var;

	k = -1;
	end = (*i) + 1;
	while ((c[end] >= 97 && c[end] <= 122) || (c[end] >= 65 && c[end] <= 90))
		end++;
	var = ft_substr(str, (*i) + 1, end - *i + 1);
	if (!var)
		return (MALLOC);
	while (env[++k])
		if (!check_name(env[k], var))
			break ;
	if (!env[k])
	{
		*i = end + 1;
		return (0);
	}
}
