/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:25:00 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/30 11:28:43 by nmota-bu         ###   ########.fr       */
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

void static	upgrade(t_min *tk, char *str)
{
	char	*pwd;
	t_env	*find;

	pwd = getcwd(NULL, 0);
	find = env_find(tk->env, str, find_env);
	if (find)
	{
		free(find->value);
		find->value = pwd;
	}
	if (!ft_strncmp("PWD", str, 4))
	{
		if (tk->pwd != NULL)
			free(tk->pwd);
		tk->pwd = ft_strdup(pwd);
	}
	else
	{
		if (tk->oldpwd != NULL)
			free(tk->oldpwd);
		tk->oldpwd = ft_strdup(pwd);
	}
}

int	ft_cd(char **args, t_min *tk)
{
	char	*path;
	int		res;

	res = 0;
	if (args[1] != NULL)
	{
		if (!ft_strncmp("~", args[1], 1))
			path = tk->home;
		else if (!ft_strncmp("-", args[1], 2))
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
		upgrade(tk, "OLDPWD");
		res = change_directory(path);
		upgrade(tk, "PWD");
	}
	return (res);
}
