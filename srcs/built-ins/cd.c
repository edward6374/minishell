/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:25:00 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/17 17:28:34 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	static change_directory(const char *path)
{
	if (chdir(path) == 0)
		return (0);
	else
	{
		perror("cd");
		return (-1);
	}
}

char static	*home_dir(char *args, t_env *env)
{
	t_env	*find;
	char	*path;

	find = env_find(env, "HOME", find_env);
	if (ft_strlen(args) > 2)
	{
		args++;
		path = ft_strjoin((const char *)find->value, args);
		return (path);
	}
	else
		return (find->value);
}

void static	upgrade_env(t_env *env, int type)
{
	char	*pwd;
	t_env	*find;

	pwd = getcwd(NULL, 0);
	if (!type)
		find = env_find(env, "OLDPWD", find_env);
	else
		find = env_find(env, "PWD", find_env);
	free(find->value);
	find->value = pwd;
}

char static	*oldpwd(t_env *env)
{
	t_env	*find;

	find = env_find(env, "OLDPWD", find_env);
	return (find->value);
}

int	ft_cd(char **args, t_env *env)
{
	char	*path;

	if (args[1] != NULL)
	{
		if (!ft_strncmp("~", args[1], 1))
			path = home_dir(args[1], env);
		else if (!ft_strncmp("-", args[1], 2))
			path = oldpwd(env);
		else
			path = args[1];
		upgrade_env(env, 0);
		change_directory(path);
		upgrade_env(env, 1);
		printf("CD: %s\n", path);
	}
	return (0);
}
