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

char	**take_env(char *env[])
{
	int		i;
	char	**new;

	i = 0;
	while (env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
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
			return (free_double_char(new, i));
	}
	new[i] = NULL;
	return (new);
}

static t_minishell	*init_struct(char **argv, char *env[])
{
	t_minishell	*tokens;

	(void)argv;
	tokens = (t_minishell *)malloc(sizeof(t_minishell));
	if (!tokens)
		return (NULL);
	tokens->env = NULL;
	if (!ft_find_path(env))
		tokens->path = NULL;
	else
	{
		tokens->path = ft_split(ft_find_path(env), ':');
		if (!tokens->path)
			return (free_struct(&tokens));
	}
	tokens->env = take_env(env);
	if (!tokens->env)
		return (free_struct(&tokens));
	tokens->command = NULL;
	tokens->num_cmds = 0;
	tokens->exit_value = 0;
//	int	i = -1;
//	while (tokens->env[++i])
//		printf("%s\n", tokens->env[i]);
//	exit(0);
	return (tokens);
}

static int	program(t_minishell *tokens, char *env[], char *string)
{
	int			err;

	add_history(string);
	err = parser(tokens, env, string);
	if (err)
	{
		printf("Error:\t");
		return (end_program(&string, err));
	}
	printf("Number of commands: %d\n", tokens->num_cmds);
	err = execute_commands(tokens);
	if (err)
	{
		printf("Execute error:\t");
		return (end_program(&string, err));
	}
	free_commands(&tokens->command);
	tokens->num_cmds = 0;
	free (string);
	string = NULL;
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	char		*string;
	t_minishell	*tokens;

	signal(SIGINT, siginthandler);
	if (argc == 1)
	{
		tokens = init_struct(argv, env);
		if (!tokens)
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
				if (program(tokens, env, string))
					break ;
		}
//		system("leaks minishell");
//		exit (0);
	}
	else
		printf("Program requires no arguments\n");
	return (0);
}
