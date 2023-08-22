/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:51:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/22 17:00:53 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"
#include "parser.h"

int change_env_list(t_parser **word_lst, t_env **env, t_vars *v, t_word data)
{
	t_env *next;

	if (!data.word || ((v->stp == 0 || v->s[v->stp - 1] == ' ') && add_word(word_lst, data.word)))
		return (MALLOC);
	else if (!data.word || (v->stp > 0 && v->s[v->stp - 1] != ' ' && join_words(word_lst, data.word)))
		return (MALLOC);
	if (data.l)
		v->stp = (*data.idx)--;
	else
		v->stp = *data.idx + ft_strlen((*env)->name);
	if (!data.l)
	{
		next = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		free(*env);
		*env = next;
		if (*env)
			(*env)->before = NULL;
	}
	return (0);
}

int before_word(t_parser **word_lst, t_vars *v, t_word *data, int *i)
{
	if (v->stp > 0 && *i - v->stp > 0 && v->s[v->stp - 1] != ' ')
	{
		data->word = ft_substr(v->s, v->stp, *i - v->stp);
		if (!data->word || create_word(word_lst, v, i, 1))
			return (2);
	}
	if (!ft_strncmp(&v->s[*i], "$?", 3))
	{
		*i += 3;
		data->l = 1;
		data->word = ft_substr(v->s, v->stp, *i - v->stp);
		return (0);
	}
	return (1);
}

int check_env_word(t_parser **word_lst, t_env **env, t_vars *v, int *i)
{
	int res;
	t_word data;

	data.l = 0;
	data.idx = i;
	res = before_word(word_lst, v, &data, i);
	if (res == 2)
		return (MALLOC);
	else if (res == 1 && (!(*env) || ft_strncmp(&v->s[*i + 1], (*env)->name,
												ft_strlen((*env)->name) - 1)))
	{
		data.l = 1;
		if (v->s[++(*i)] == '?')
			(*i)++;
		while (ft_isalnum(v->s[(*i)]))
			(*i)++;
		data.word = ft_strdup("");
	}
	else if (res == 1)
		data.word = ft_strdup((*env)->value);
	return (change_env_list(word_lst, env, v, data));
}

static t_env *new_list_elem(t_env *found, t_env **old_tmp, t_vars *v, int *i)
{
	int count;
	t_env *new;

	count = *i + 1;
	while ((v->s[count] >= 'a' && v->s[count] <= 'z') || (v->s[count] >= 'A' && v->s[count] <= 'Z') || (v->s[count] >= '0' && v->s[count] <= '9'))
		count++;
	*i = count - 1;
	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_strdup(found->name);
	new->value = ft_strdup(found->value);
	if (old_tmp)
	{
		(*old_tmp)->next = new;
		new->before = *old_tmp;
	}
	return (new);
}

// TODO
// Borrar esta funcion al final
// static int	print_list(t_env *env_list)
// {
// 	t_env	*tmp;

// 	tmp = env_list;
// 	while (tmp)
// 	{
// 		printf("Env: %s\n", tmp->name);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

t_env *find_env_vars(t_env *env, t_vars *v)
{
	int i;
	t_env *tmp;
	t_env *found;
	t_env *env_list;

	env_list = NULL;
	i = v->stp - 1;
	while (++i < v->i)
	{
		check_quotes(v, &v->s[i]);
		if ((v->oq || v->dq) && v->s[i] == '$')
		{
			found = search_env(env, &v->s[i + 1], find_env);
			if (found && !env_list)
			{
				env_list = new_list_elem(found, NULL, v, &i);
				tmp = env_list;
			}
			else if (found)
				tmp = new_list_elem(found, &tmp, v, &i);
			printf("Found: %p\n", found);
		}
	}
	// print_list(env_list);
	return (env_list);
}
