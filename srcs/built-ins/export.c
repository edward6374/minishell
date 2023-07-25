/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:48:56 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/25 20:39:25 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	loop_all_env(char **env, int small)
{
	int	i;
	int	last;

	i = -1;
	last = 0;
	while (env[++i])
		if (ft_strncmp(env[i], env[last], ft_strlen(env[small])) > 0)
			last = i;
	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], env[small], ft_strrchr(env[small], '=') \
			- env[small] + 1) > 0
			&& ft_strncmp(env[i], env[last], ft_strrchr(env[last], '=') \
			- env[last] + 1) < 0)
			last = i;
	small = last;
	return (small);
}

int	print_env(char **env)
{
	int	len;
	int	num;
	int	small;

	len = -1;
	num = -1;
	small = 0;
	while (env[++num])
		if (ft_strncmp(env[num], env[small], ft_strlen(env[small])) < 0)
			small = num;
	printf("declare -x %s\n", env[small]);
	while (++len < num - 1)
	{
		small = loop_all_env(env, small);
		printf("declare -x %s\n", env[small]);
	}
	return (0);
}

int	add_vars(t_cmd *temp, char **new_env, int i)
{
	int	k;

	k = 0;
	while (temp->args[++k])
	{
		if (!ft_isalpha(temp->args[k][0]) && temp->args[k][0] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", \
				temp->args[k]);
			continue ;
		}
		new_env[i] = ft_strdup(temp->args[k]);
		if (!new_env[i])
			return (free_double_int(new_env, i));
		i++;
	}
	new_env[i] = NULL;
	return (0);
}

int	ft_export(t_min *tk, t_cmd *temp)
{
	int		i;
	char	**new_env;

	if (!temp->args[1] || (temp->args[1] && temp->args[1][0] == '$'))
		return (print_env(tk->env_vars));
	i = 0;
	while (tk->env_vars[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (MALLOC);
	i = -1;
	while (tk->env_vars[++i])
	{
		new_env[i] = ft_strdup(tk->env_vars[i]);
		if (!new_env[i])
			return (free_double_int(new_env, i));
	}
	if (add_vars(temp, new_env, i))
		return (MALLOC);
	free_double_void(tk->env_vars);
	tk->env_vars = new_env;
	return (0);
}
