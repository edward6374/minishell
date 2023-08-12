/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:08:59 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/12 07:29:28 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

// TODO
// actualizar el SHLVL, PWD

void	siginthandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		//poner algo aqui
	}
}

static int	program(t_min *tk, char *env[], char *line)
{
	int	err;

	add_history(line);
	err = parser(tk, env, line);
	if (err)
	{
		printf("Parser error:\t");
		return (end_program(&line, err));
	}
	printf("Number of commands: %d\n", tk->num_cmds);
	err = execute_commands(tk);
	if (err)
	{
		printf("Execute error:\t");
		return (end_program(&line, err));
	}
	if (tk->cmds)
		free_commands(&tk->cmds);
	tk->num_cmds = 0;
	free(line);
	return (0);
}

static t_min	*init_struct(char *env[])
{
	t_min	*tk;

	tk = ft_calloc(1, sizeof(t_min));
	if (!tk)
		return (NULL);
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
//	tk->cmds = NULL;
//	tk->num_cmds = 0;
//	tk->exit_value = 0;
	//	int	i = -1;
	//	while (tk->env[++i])
	//		printf("%s\n", tk->env[i]);
	//	exit(0);
	return (tk);
}

int	main(int argc, char *argv[], char *env[])
{
	t_min	*tk;
	char	*line;

	signal(SIGINT, siginthandler);
	signal(SIGQUIT, siginthandler);
	if (argc == 1)
	{
		tk = init_struct(env);
		if (!tk)
			return (end_program(NULL, MALLOC));
		while (42)
		{
//			line = readline("\033[1;32m min\033[1;37"
//								"mis\033[1;31mhell\033[0;0m> ");
			line = readline(get_curr_path());
			if (!line)
			{
				printf("NULL\n");
				return (d_key(&tk));
			}
			else if (line && line[0] == '\0')
				free(line);
			else if (program(tk, env, line))
				break ;
		}
		//		system("leaks minishell");
		//		exit (0);
	}
	else
		printf("Program requires no arguments\n");
	return (0);
}
