/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:25:41 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/21 11:44:09 by nmota-bu         ###   ########.fr       */
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

int	export_add(t_env *env, char **args)
{
	int		i;
	t_env	*find;
	char	*name;
	char	*value;

	find = NULL;
	i = 1;
	if (args[0])
		while (args[i] != NULL)
		{
			name = ft_substr(args[i], 0, ft_strcspn(args[i], "="));
			value = ft_substr(args[i], (ft_strlen(name) + 1), 0xFFFFFFF);
			if (!is_name(name))
			{
				printf("minishell: export: `%s\': not a valid identifier\n",
						args[i]);
				return (MALLOC);
			}
			if (!env_find(env, name, find_env))
				env_add_back(&env, new_env(name, value));
			else
			{
				find = env_find(env, name, find_env);
				free(find->value);
				find->value = value;
			}
			free(name);
			i++;
		}
	return (0);
}
