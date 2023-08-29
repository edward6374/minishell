/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:25:00 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/29 16:23:23 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int static	change_directory(const char *path)
{
	if (chdir(path) == 0)
		return (0);
	else
	{
		perror("cd");
		g_exit = 1;
		return (1);
	}
}

// char static	*home_dir(char *args, t_env *env)
// {
// 	t_env	*find;
// 	char	*path;

// 	find = env_find(env, "HOME", find_env);
// 	if (ft_strlen(args) > 2)
// 	{
// 		args++;
// 		path = ft_strjoin((const char *)find->value, args);
// 		return (path);
// 	}
// 	else
// 		return (find->value);
// }

// controlar si hay OLDPWD o PWD
void static upgrade_old(t_min *tk)
{
	char *pwd;
	t_env *find;

	pwd = getcwd(NULL, 0);
	find = env_find(tk->env, "OLDPWD", find_env);
	if (find)
	{
		free(find->value);
		find->value = pwd;
	}
	if (tk->oldpwd != NULL)
		free(tk->oldpwd);
	tk->oldpwd = ft_strdup(pwd);
}

void static upgrade_pwd(t_min *tk)
{
	char	*pwd;
	t_env	*find;

	pwd = getcwd(NULL, 0);
	find = env_find(tk->env, "PWD", find_env);
	if (find)
	{
		free(find->value);
		find->value = pwd;
	}
	if (tk->pwd != NULL)
		free(tk->pwd);
	tk->pwd = ft_strdup(pwd);
}

// else
// {
// 	find = env_find(tk->env, "PWD", find_env);
// }

// char static *oldpwd(t_env *env)
// {
// 	t_env *find;

// 	find = env_find(env, "OLDPWD", find_env);
// 	return (find->value);
// }

int ft_cd(char **args, t_min *tk)
{
	char *path;
	int res;

	res = 0;
	if (args[1] != NULL)
	{
		if (!ft_strncmp("~", args[1], 1))
			// path = home_dir(args[1], tk->env);
			path = tk->home;
		else if (!ft_strncmp("-", args[1], 2))
		// path = oldpwd(tk->env);
		{
			if (!tk->oldpwd)
			{
				printf(":( cd: OLDPWD not set\n");
				return (res);
			}
			path = tk->oldpwd;
		}
		else
			path = args[1];
		upgrade_old(tk);
		res = change_directory(path);
		upgrade_pwd(tk);
		// upgrade_pwd(tk);
	}
	return (res);
}

// si no hay
// bash: cd: OLDPWD not set
