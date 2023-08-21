/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:51:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/21 21:59:48 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "built-ins.h"

int	env_word(t_parser **word_lst, t_env **env, t_vars *v, int *i)
{
	char	*word;
	t_env	*next;

	printf("Env word: %s\tStart: %d\tChar: %c\n", (*env)->value, v->stp, v->s[v->stp]);
	if (v->stp > 0 && *i - v->stp > 0 && v->s[v->stp - 1] != ' ')
	{
		word = ft_substr(v->s, v->stp, *i - v->stp);
		if (!word || create_word(word_lst, v, i, 1))
			return (MALLOC);
	}
	word = ft_strdup((*env)->value);
	if (!word || ((v->stp == 0 || v->s[v->stp - 1] == ' ')
		&& add_word(word_lst, word)))
		return (MALLOC);
	else if (!word || (v->stp > 0 && v->s[v->stp - 1] != ' '
		&& join_words(word_lst, word)))
		return (MALLOC);
	v->stp = *i + ft_strlen((*env)->name);
	next = (*env)->next;
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = next;
	if (*env)
		(*env)->before = NULL;
	printf("End adding env\n");
	return (0);
}

int	add_env_var(t_word *w , t_env **env)
{
	int		i;
	t_env	*next;

	i = -1;
	printf("Add env var\n");
	while ((*env)->value[++i])
		w->word[++w->l] = (*env)->value[i];
	w->i += i;
	next = (*env)->next;
	free((*env)->name);
	free((*env)->value);
	free(*env);
	*env = next;
	(*env)->before = NULL;
	return (0);
}

static t_env	*new_list_elem(t_env *found, t_env **old_tmp,
	t_vars *v, int *i)
{
	int		count;
	t_env	*new;

	count = *i + 1;
	while ((v->s[count] >= 'a' && v->s[count] <= 'z')
		|| (v->s[count] >= 'A' && v->s[count] <= 'Z')
		|| (v->s[count] >= '0' && v->s[count] <= '9'))
		count++;
	*i = count - 1;
	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_strdup(found->name);
	new->value = ft_strdup(found->value);
	printf("New elem name: %s\tValue: %s\n", new->name, new->value);
	if (old_tmp)
	{
		(*old_tmp)->next = new;
		new->before = *old_tmp;
	}
	return (new);
}

static int	print_list(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("Env: %s\n", tmp->name);
		tmp = tmp->next;
	}
	return (0);
}

t_env	*find_env_vars(t_env *env, t_vars *v)
{
	int		i;
	t_env	*tmp;
	t_env	*found;
	t_env	*env_list;

	env_list = NULL;
	i = v->stp - 1;
	while (++i < v->i)
	{
		check_quotes(v, &v->s[i]);
		if ((v->oq || v->dq) && v->s[i] == '$')
		{
			printf("Char: %c\tNext: %c\n", v->s[i], v->s[i + 1]);
			found = env_find(env, &v->s[i + 1], find_env);
			if (found && !env_list)
			{
				printf("Found one\n");
				env_list = new_list_elem(found, NULL, v, &i);
				tmp = env_list;
			}
			else if (found)
			{
				printf("Found another one\n");
				tmp = new_list_elem(found, &tmp, v, &i);
			}
		}
	}
	print_list(env_list);
	printf(RED "End finding env\n" NO_COLOR);
	return (env_list);
}