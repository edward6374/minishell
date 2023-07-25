/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2023/06/04 16:08:59 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	take_env(t_min *tk, char *env[])
{
	int		i;
	char	**new;

	i = 0;
	while (env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (MALLOC);
	i = -1;
	while (env[++i])
	{
		if (!check_name(env[i], "SHLVL"))
			new[i] = ft_strjoin(ft_substr(env[i], 0, 6), \
				ft_itoa(ft_atoi(ft_strrchr(env[i], '=') + 1) + 1));
		else if (!check_name(env[i], "OLDPWD"))
			new[i] = ft_substr(env[i], 0, 7);
		else
			new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (free_double_int(new, i));
	}
	new[i] = NULL;
	tk->env_vars = new;
	return (0);
}

static t_min	*init_struct(char **argv, char *env[])
{
	t_min	*tk;

	(void)argv;
	tk = (t_min *)malloc(sizeof(t_min));
	if (!tk)
		return (NULL);
	tk->env_vars = NULL;
	if (!ft_find_path(env))
		tk->path = NULL;
	else
	{
		tk->path = ft_split(ft_find_path(env), ':');
		if (!tk->path)
			return (free_struct(&tk));
	}
	if (take_env(tk, env))
		return (free_struct(&tk));
	tk->cmds = NULL;
	tk->num_cmds = 0;
	tk->exit_value = 0;
//	int	i = -1;
//	while (tk->env[++i])
//		printf("%s\n", tk->env[i]);
//	exit(0);
	return (tk);
}

static int	program(t_min *tk, char *env[], char *string)
{
	int			err;

	add_history(string);
	err = parser(tk, env, string);
	if (err)
	{
		printf("Error:\t");
		return (end_program(&string, err));
	}
	printf("Number of commands: %d\n", tk->num_cmds);
	err = execute_commands(tk);
	if (err)
	{
		printf("Execute error:\t");
		return (end_program(&string, err));
	}
	free_commands(&tk->cmds);
	tk->num_cmds = 0;
	free (string);
	string = NULL;
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	t_min		*tk;
	char		*string;

	signal(SIGINT, siginthandler);
	if (argc == 1)
	{
		tk = init_struct(argv, env);
		if (!tk)
			return (end_program(NULL, MALLOC));
		while (42)
		{
			string = readline("\033[1;32m min\033[1;37"
					"mis\033[1;31mhell\033[0;0m> ");
			if (!string)
				return (d_key());
			else if (string && string[0] == '\0')
				free(string);
			else
				if (program(tk, env, string))
					break ;
		}
//		system("leaks minishell");
//		exit (0);
	}
	else
		printf("Program requires no arguments\n");
	return (0);
}
