/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:25:41 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/23 22:11:42 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"
#include "libft.h"

t_env	*new_env(char *str, char *value)
{
	t_env	*new;
	char	*name;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	name = ft_strjoin(str, "=");
	new->name = name;
	if (ft_strlen(value) == 0)
		new->value = NULL;
	else
		new->value = value;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (*env == NULL)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
}

int	is_name(char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void static	change_value(t_env *env, t_export dt)
{
	dt.find = env_find(env, dt.name, find_env);
	free(dt.find->value);
	dt.find->value = dt.value;
}

int	export_add(t_env *env, char **args)
{
	t_export	dt;

	dt.find = NULL;
	dt.i = 1;
	if (args[0])
		while (args[dt.i] != NULL)
		{
			dt.name = ft_substr(args[dt.i], 0, ft_strcspn(args[dt.i], "="));
			dt.value = ft_substr(args[dt.i], (ft_strlen(dt.name) + 1),
					0xFFFFFFF);
			if (!is_name(dt.name))
			{
				printf("minishell: export: `%s\': not a valid identifier\n",
						args[dt.i]);
				return (1);
			}
			if (!env_find(env, dt.name, find_env))
				env_add_back(&env, new_env(dt.name, dt.value));
			else
				change_value(env, dt);
			free(dt.name);
			dt.i++;
		}
	return (0);
}
