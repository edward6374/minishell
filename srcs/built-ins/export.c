/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:48:56 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/10 11:46:27 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"
#include "minishell.h"

t_env	*loop_all_env(t_env *env, t_env *small)
{
	t_env	*temp;
	t_env	*last;

	last = env;
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->str, last->str, ft_strlen(last->str)) > 0)
			last = temp;
		temp = temp->next;
	}
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->str, small->str, ft_strrchr(small->str, '=')
				- small->str + 1) > 0 && ft_strncmp(temp->str, last->str,
				ft_strrchr(last->str, '=') - last->str + 1) < 0)
			last = temp;
		temp = temp->next;
	}
	small = last;
	return (small);
}

int	print_env(t_env *env)
{
	int		i;
	int		len;
	t_env	*temp;
	t_env	*small;

	i = -1;
	len = 0;
	temp = env;
	small = env;
	while (temp)
	{
		if (ft_strncmp(temp->name, small->name, ft_strlen(small->name)) < 0)
			small = temp;
		temp = temp->next;
		len++;
	}
	printf("declare -x %s%s\n", small->name, small->value);
	while (++i < len - 1)
	{
		small = loop_all_env(env, small);
		printf("declare -x %s%s\n", small->name, small->value);
	}
	return (0);
}

int	add_update_var(t_env *env, char *new, int mode)
{
	int	i;
	int	s_q;
	int	d_q;

	s_q = 0;
	d_q = 0;
	if (mode && ft_strrchr(new, '\'') && ft_strrchr(new, '\"'))
	{
		printf("minishell: export: %s: not a valid identifier\n");
		return (0);
	}
	if (!mode)
	{
		free(env->value);
		i = ft_strrchr(new, '=') - new;
		if (new[i + 1] == '\"')
			i++;
		while (new[++i])
		{
		}
	}
}

int	ft_export(t_min *tk, t_cmd *temp, int p)
{
	int		i;
	int		res;
	t_env	*env;

	i = 0;
	res = 0;
	if (!temp->args[1] || (temp->args[1] && temp->args[1][0] == '$'))
		return (print_env(tk->env));
	while (temp->args[++i])
	{
		env = tk->env;
		while (env)
		{
			if (ft_strrchr(temp->args[i], '=') && !ft_strncmp(temp->args[i],
					env->name, ft_strlen(env->name)))
			{
				if (add_update_var(env, temp->args[i], 0))
					return (MALLOC);
				break ;
			}
			env = env->next;
		}
		if (!env && add_update_var(tk_env, temp->args[i], 1))
			return (MALLOC);
	}
	return (0);
}
