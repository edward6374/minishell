/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:48:56 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/13 17:57:11 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

// TODO
// para tu libreria
//=========================================================================
int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int ft_len_dptr(char **arr)
{
	int i;

	i = -1;
	while (arr[++i] != NULL)
		;
	return (i);
}

void ft_print_dptr(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
//=========================================================================

void static print_export(char **arr)
{
	int i;

	i = -1;
	if (arr == NULL)
		return;
	while (arr[++i] != NULL)
		printf("declare -x %s\n", arr[i]);
}

void static custom_qsort(char **env, size_t size)
{
	char *tmp;
	size_t i;
	size_t j;
	size_t j_min;

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

char *insert_quotes(char *input)
{
	t_qoutes data;

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

int ft_export(t_min *tk, t_cmd *tmp, int p)
{
	(void)p;
	char **env;
	int i;

	env = take_double(tk->env);
	if (tmp->args[1] == NULL)
	{
		i = -1;
		while (env[++i] != NULL)
			env[i] = insert_quotes(env[i]);
		custom_qsort(env, ft_len_dptr(env));
		print_export(env);
	}
	else
	{
		ft_print_dptr(tmp->args);
		export_add();
	}

	return (0);
}
