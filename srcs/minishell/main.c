/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:08:59 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/13 18:27:24 by nmota-bu         ###   ########.fr       */
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
// {
// 	char	*path;
// 	char	get_path[256];

// 	getcwd(get_path, sizeof(get_path));
// 	path = ft_strjoin("\033[0;96m", get_path);
// 	if (!path)
// 		return (NULL);
// 	path = ft_strjoin(path, "\033[0;0m$ ");
// 	if (!path)
// 		return (NULL);
// 	return (path);
// }

void	siginthandler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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

int	main(int argc, char *argv[], char *env[])
{
	t_min	*tk;
	char	*line;

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
