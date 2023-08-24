/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:06:26 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/24 17:40:41 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Buscar en la lista el nodo con nombre PATH y devuelve solo el valor

#include "built_ins.h"
#include "minishell.h"
#include "parser.h"

char	*ft_envfind_to_dptr(t_env *env, void *data_ref, int (*cmp)(char *,
			char *, int))
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if ((*cmp)(curr->name, data_ref, 1) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

int static	ft_len_token(char *str, char *token)
{
	int	i;

	i = 0;
	while (str != NULL)
	{
		i++;
		str = ft_strtok(NULL, token);
	}
	return (i);
}

char static	*find_env_to_ptr(t_env *env)
{
	char	*res;

	res = ft_envfind_to_dptr(env, "PATH", find_env);
	return (res);
}

// pasa los PATH  de la lista env a doble ptr

char	**path_env(t_env *env)
{
	t_path_env	data;

	data.res = find_env_to_ptr(env);
	if (!data.res)
		return (NULL);
	data.path_copy = ft_strdup(data.res);
	data.token = ft_strtok(data.path_copy, ":");
	data.num_paths = ft_len_token(data.token, ":");
	data.paths = (char **)malloc((data.num_paths + 1) * sizeof(char *));
	free(data.path_copy);
	data.path_copy = ft_strdup(data.res);
	data.token = ft_strtok(data.path_copy, ":");
	data.i = -1;
	while (++data.i < data.num_paths)
	{
		data.paths[data.i] = ft_strdup(data.token);
		data.token = ft_strtok(NULL, ":");
	}
	data.paths[data.i] = NULL;
	free(data.path_copy);
	return (data.paths);
}
