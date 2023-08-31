/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 11:02:42 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/31 18:35:53 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*save_node(t_min *tk, t_env *new, t_env *old_tmp)
{
	t_env	*tmp;

	if (!old_tmp)
	{
		new->before = NULL;
		tk->env = new;
		tmp = tk->env;
	}
	else
	{
		old_tmp->next = new;
		old_tmp->next->before = old_tmp;
		tmp = old_tmp->next;
	}
	return (tmp);
}

// void	print_env(t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		printf("Name: %s\tValue: %s\n", tmp->name, tmp->value);
// 		tmp = tmp->next;
// 	}
// }

void	check_oldpwd(t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "OLDPWD", 6))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		tmp = env->next->next->next->next->next->next->next;
		new = ft_calloc(1, sizeof(t_env));
		new->name = ft_strdup("OLDPWD=");
		new->value = NULL;
		new->next = tmp->next;
		new->before = tmp;
		tmp->next = new;
	}
}

int	take_env(t_min *tk, char *env[])
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	i = -1;
	tmp = NULL;
	while (env[++i])
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			return (MALLOC);
		new->name = ft_substr(env[i], 0, ft_strrchr(env[i], '=') - env[i] + 1);
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			new->value = ft_strdup(ft_itoa(ft_atoi(ft_strrchr(env[i], '=') + 1)
						+ 1));
		else if (!ft_strncmp(env[i], "OLDPWD", 6))
			new->value = NULL;
		else
			new->value = ft_strdup(ft_strrchr(env[i], '=') + 1);
		if (!new->name || (ft_strncmp(new->name, "OLDPWD=", 7) && !new->value))
			return (free_env(new));
		tmp = save_node(tk, new, tmp);
	}
	check_oldpwd(tk->env);
	return (0);
}
