/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:25:41 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/13 20:21:15 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

//=============tmp=====================================================

void ft_print_dptr_v2(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return;
	while (arr[i] != NULL)
	{
		printf("\t%s\n", arr[i]);
		i++;
	}
}

//=========================================================================

// Encuentra el valor, del nombre pasado en un lista

int find_env(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (1);
	}
	if (s1[i] == '=')
		return (0);
	return (1);
}

t_env *env_find(t_env *env, void *data_ref, int (*cmp)(char *, char *))
{
	t_env *curr;

	curr = env;
	while (curr)
	{
		if ((*cmp)(curr->name, data_ref) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_env *env_new(void *content)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(content);
	new->next = NULL;
	return (new);
}

void env_add_back(t_env **env, t_env *new_node)
{
	t_env *tmp;

	if (*env == NULL)
	{
		*env = new_node;
		return;
	}
	tmp = *env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
}

void export_add(t_env *env, char **args)
{
	int i;
	t_env *find;
	char *tmp;

	find = NULL;
	i = 1;

	ft_print_dptr_v2(args);
	while (args[i] != NULL)
	{
		tmp = ft_substr(args[i], 0, ft_strcspn(args[i], "="));

		if (!env_find(env, tmp, find_env))
		{
			printf("\ttmp:%s\n", tmp);
		}
		else
		{
			printf("Si esta\n");
		}
		i++;
	}
}
