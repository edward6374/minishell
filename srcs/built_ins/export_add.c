/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:25:41 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/30 20:53:36 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "libft.h"

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

int static	is_name(char *name)
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

void	remove_plus(char *str)
{
	int	len;

	len = strlen(str);
	if (len > 0 && str[len - 1] == '+')
		str[len - 1] = '\0';
}

void	export_loop(t_env *env, char **args, t_export *dt)
{
	if (!is_name(dt->name))
	{
		printf("%s export: `%s\': not valid identifier\n", TERROR, args[dt->i]);
		dt->res = 1;
		dt->name = NULL;
	}
	if (dt->name != NULL)
	{
		if (!env_find(env, dt->name, find_env))
			env_add_back(&env, new_env(dt->name, dt->value));
		else
		{
			dt->find = env_find(env, dt->name, find_env);
			free(dt->find->value);
			dt->find->value = dt->value;
		}
	}
}

int	export_add(t_env *env, char **args)
{
	t_export	dt;

	dt.find = NULL;
	dt.i = 1;
	dt.res = 0;
	if (args[0])
	{
		while (args[dt.i] != NULL)
		{
			dt.name = ft_substr(args[dt.i], 0, ft_strcspn(args[dt.i], "="));
			dt.value = ft_substr(args[dt.i], (ft_strlen(dt.name) + 1),
					0xFFFFFFF);
			remove_plus(dt.name);
			export_loop(env, args, &dt);
			dt.i++;
		}
	}
	return (dt.res);
}
