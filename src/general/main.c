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

#include "../../inc/minishell.h"

/*
t_command	*add_elem(char *cmd, char **args)
{
	t_command	*tok;

	tok = (t_command *)malloc(sizeof(t_command));
	if (!tok)
		return (NULL);
	tok->cmd = cmd;
	tok->args = args;
	tok->next = NULL;
	return (tok);
}
*/

/*
static int	ft_readline(t_minishell *tokens, char *env[])
{
	char	*string;

	string = readline("\033[1;32m min\033[1;37"
			"mis\033[1;31mhell\033[0;0m> ");
	if (!string)
	{
		rl_clear_history();
		printf("exit\n");
		return (1) ;
	}
	else if (string && string[0] == '\0')
		free(string);
	else if (string && string[0] != '\0')
	{
		add_history(string);
		//		parser(tokens, env, string);
		minishell(tokens, env, string);
		free (string);
	}
	string = NULL;
	return (0);
}
*/

static t_minishell	*init_struct(char *env[])
{
	t_minishell	*tokens;

	tokens = (t_minishell *)malloc(sizeof(t_minishell));
	if (!tokens)
	{
//		perror("Malloc error");
		return (NULL);
	}
	if (!ft_find_path(env))
		tokens->path = NULL;
	else
	{
		tokens->path = ft_split(ft_find_path(env), ':');
		if (!tokens->path)
		{
			free(tokens);
			tokens = NULL;
//			perror("Malloc error");
			return (NULL);
		}
	}
	tokens->command = NULL;
	return (tokens);
}

static int	program(char *env[], char *string)
{
	int			err;
	t_minishell	*tokens;

	add_history(string);
	tokens = init_struct(env);
	if (!tokens)
		return (end_program(&string, MALLOC));
	err = parser(tokens, env, string);
	if (err)
	{
		printf("Error\n");
		return (end_program(&string, err));
	}
	minishell(tokens, env, string);
	free_tokens(&tokens);
	free (string);
	string = NULL;
	return (0);
}

void	siginthandler(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int argc, char *argv[], char *env[])
{
	char	*string;

	(void)argv;
	signal(SIGINT, siginthandler);
	if (argc == 1)
	{
		while (1)
		{
			string = readline("\033[1;32m min\033[1;37"
					"mis\033[1;31mhell\033[0;0m> ");
			if (!string)
				return (d_key());
			else if (string && string[0] == '\0')
				free(string);
			else
				if (program(env, string))
					break ;
		}
//		system("leaks minishell");
//		exit (0);
	}
	else
		printf("Program requires no arguments\n");
	return (0);
}
