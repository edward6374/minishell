/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:08:59 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/14 12:02:10 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

char	*get_curr_path(void)
{
	char *pwd;
	char *tmp;

	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("\033[0;33m", pwd);
	free(pwd);
	pwd = ft_strjoin(tmp, "$ \033[0;37m");
	free(tmp);
	return (pwd);
}

static int	program(t_min *tk, char *line)
{
	int	err;

	add_history(line);
	err = parser(tk, line);
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
		{
			free(tk);
			return (NULL);
		}
	}
	if (take_env(tk, env))
	{
		free_double_void(tk->path);
		free(tk);
		return (NULL);
	}
//	int	i = -1;
//	while (tk->env[++i])
//		printf("%s\n", tk->env[i]);
//	exit(0);
	return (tk);
}

int	loop_main(t_min *tk)
{
	char	*path;
	char	*line;

	path = get_curr_path();
	line = readline(path);
	if (!line)
	{
		printf("NULL\n");
		return (free_pointer(path, 1));
	}
	else if (line && line[0] == '\0')
		free(line);
	else if (program(tk, line))
		return (free_pointer(path, 2));
	free(path);
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	int		result;
	t_min	*tk;

	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, siginthandler);
	if (argc == 1)
	{
		tk = init_struct(env);
		if (!tk)
			return (end_program(NULL, MALLOC));
		while (42)
		{
			result = loop_main(tk);
			if (result == 1)
				return (d_key(&tk));
			else if (result == 2)
				break ;
//			line = readline("\033[1;32m min\033[1;37"
//								"mis\033[1;31mhell\033[0;0m> ");
		}
		//		system("leaks minishell");
		//		exit (0);
	}
	else
		printf("Program requires no arguments\n");
	return (0);
}
