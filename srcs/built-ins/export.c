/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:48:56 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/27 16:37:22 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

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
		if (ft_strncmp(temp->str, small->str, ft_strrchr(small->str, '=') \
			- small->str + 1) > 0
			&& ft_strncmp(temp->str, last->str, ft_strrchr(last->str, '=') \
			- last->str + 1) < 0)
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
		if (ft_strncmp(temp->str, small->str, ft_strlen(small->str)) < 0)
			small = temp;
		temp = temp->next;
		len++;
	}
	printf("declare -x %s\n", small->str);
	while (++i < len - 1)
	{
		small = loop_all_env(env, small);
		printf("declare -x %s\n", small->str);
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
		printf("I: %d\tArg: %p\t%s\tNew: %p\t%s\n", i, temp->args[k], temp->args[k], new_env[i], new_env[i]);
		if (!new_env[i])
			return (free_double_int(new_env, i));
		i++;
	}
	printf("I in the end: %d\n", i);
	new_env[i] = NULL;
	return (0);
}

int	ft_export(t_min *tk, t_cmd *temp)
{
	t_env	*new_list;
	t_env	*new_elem;
	t_env	*new_temp;
	t_env	*loop;

	loop = tk->env;
	new_list = NULL;
	if (!temp->args[1] || (temp->args[1] && temp->args[1][0] == '$'))
		return (print_env(tk->env));
	while (loop)
	{
		new_elem = (t_env *)malloc(sizeof(t_env));
		if (!new_elem)
			return (free_tokens(&tk, NULL, 1));
		new_elem->next = NULL;
		new_elem->str = ft_strdup(loop->str);
		if (!new_elem->str)
		{
			free(new_elem);
			return (free_tokens(&tk, NULL, 1));
		}
		if (!new_temp)
			((new_list = new_elem) && (new_list->before = NULL) \
			 && (new_temp = new_list));
		else
			((new_temp->next = new_elem) \
			 && (new_temp->next->before = new_temp) \
			 && (new_temp = new_temp->next));
		loop = loop->next;
	}
//	*new_env = (char **)malloc(sizeof(char *) * (i + 1));
//	if (!*new_env)
//		return (MALLOC);
//	i = -1;
//	while ((*old_env)[++i])
//	{
//		(*new_env)[i] = ft_strdup((*old_env)[i]);
//		if (!(*new_env)[i])
//			return (free_double_int(*new_env, i));
//	}
//	if (add_vars(temp, *new_env, i))
//		return (MALLOC);
//	free_double_void(*old_env);
//	free(old_env);
//	tk->env_vars = new_env;
//	print_env(*new_env);
//	i = -1;
//	while (*tk->env_vars[++i])
//		printf("New env: %s\t%p\n", *tk->env_vars[i], *tk->env_vars[i]);
	return (0);
}
