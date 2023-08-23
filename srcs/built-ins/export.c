/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:48:56 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/23 21:44:22 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

void static	print_export(char **arr)
{
	int	i;

	i = -1;
	if (arr == NULL)
		return ;
	while (arr[++i] != NULL)
		printf("declare -x %s\n", arr[i]);
}

void static	custom_qsort(char **env, size_t size)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	j_min;

	i = -1;
	while (++i < size - 1)
	{
		j_min = i;
		j = i + 1;
		while (++j < size)
		{
			if (env[j_min] && env[j] && ft_strcmp(env[j], env[j_min]) < 0)
				j_min = j;
		}
		if (j_min != i)
		{
			tmp = env[i];
			env[i] = env[j_min];
			env[j_min] = tmp;
		}
	}
}

char static	*insert_quotes(char *input)
{
	t_quotes	data;

	data.len = ft_strlen(input);
	data.tmp = malloc((data.len + 3) * sizeof(char *));
	data.i = 0;
	data.j = 0;
	while (input[data.i] != '\0')
	{
		if (input[data.i] == '=')
		{
			data.tmp[data.j] = input[data.i];
			data.j++;
			data.tmp[data.j] = '"';
		}
		else
			data.tmp[data.j] = input[data.i];
		data.i++;
		data.j++;
	}
	data.tmp[data.j] = '"';
	data.tmp[data.j + 1] = '\0';
	free(input);
	return (data.tmp);
}

int	ft_export(t_min *tk, t_cmd *tmp)
{
	char	**env;
	int		i;

	if (tmp->args[1] == NULL)
	{
		env = take_double(tk, tk->env);
		i = -1;
		while (env[++i] != NULL)
			env[i] = insert_quotes(env[i]);
		custom_qsort(env, ft_len_dptr(env));
		print_export(env);
		ft_free_dptr(env);
		return (0);
	}
	else
		return (export_add(tk->env, tmp->args));
}
