/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:08:59 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/18 12:22:56 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

char	*get_curr_path(void)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("\033[0;33m", pwd);
	free(pwd);
	pwd = ft_strjoin(tmp, "$ \033[0;37m");
	free(tmp);
	return (pwd);
}

t_min	*init_struct(char *env[])
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
	return (tk);
}

int	program(t_min *tk, char *line)
{
	int	err;

	add_history(line);
	// printf("TOKEMO\n");
	err = parser(tk, line);
	((err == MALLOC) && (exit_error(g_error_array[err - 1], err)));
	if (err)
	{
		printf("Parser error:\t");
		return (end_program(&line, err));
	}
	//	printf("Number of commands: %d\n", tk->num_cmds);
	err = execute_commands(tk);
	((err == MALLOC) && (exit_error(g_error_array[err - 1], err)));
	if (err)
	{
		printf("Execute error:\t");
		return (end_program(&line, err));
	}
	if (tk->cmds)
		free_commands(&tk->cmds, 0);
	tk->num_cmds = 0;
	free(line);
	return (0);
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
	{
		free(line);
		return (0);
	}
	program(tk, line);
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
		}
	}
	else
		printf("Program requires no arguments\n");
	return (0);
}
