/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:01 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/25 20:24:51 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	change_env(t_min *tk, t_cmd *temp, char **new_env)
{
	int	i;
	int	l;
	int	k;

	l = 0;
	i = -1;
	while (tk->env_vars[++i])
	{
		k = 0;
		while (temp->args[++k])
		{
			if (!ft_strncmp(temp->args[k], tk->env_vars[i], \
				ft_strlen(temp->args[k])))
				break ;
		}
		if (!temp->args[k])
		{
			new_env[l] = ft_strdup(tk->env_vars[i]);
			if (!new_env[l])
				return (free_double_int(new_env, l));
			l++;
		}
	}
	new_env[l] = NULL;
	free_double_void(tk->env_vars);
	tk->env_vars = new_env;
	return (0);
}

int	ft_unset(t_min *tk, t_cmd *temp)
{
	int		j;
	int		k;
	int		count;
	char	**new_env;

	k = 0;
	j = 0;
	count = 0;
	printf("Unset\n");
	if (!temp->args[1])
		return (0);
	while (temp->args[++k])
		count++;
	while (tk->env_vars[j])
		j++;
	new_env = (char **)malloc(sizeof(char *) * (j - count + 1));
	if (!new_env)
		return (MALLOC);
	return (change_env(tk, temp, new_env));
}
