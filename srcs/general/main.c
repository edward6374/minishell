/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:08:59 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/29 20:09:19 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signalm.h"

unsigned char	g_exit = 0;

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
	if (take_env(tk, env))
	{
		free(tk);
		return (NULL);
	}
	return (tk);
}

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("Name: %s\tValue: %s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	program(t_min *tk, char *line)
{
	int	err;

	add_history(line);
	err = parser(tk, line);
	if (err == MALLOC)
		exit_error(g_error_array[err - 1], err);
	else if (err)
	{
		end_program(&line, err);
		return ;
	}
	err = execute_commands(tk);
	if (err == MALLOC)
		exit_error(g_error_array[err - 1], err);
	else if (err)
	{
		end_program(&line, err);
		return ;
	}
	if (tk->cmds)
		free_commands(&tk->cmds, 0);
	tk->num_cmds = 0;
	free(line);
}

int	loop_main(t_min *tk)
{
	char	*path;
	char	*line;

	path = get_curr_path();
	line = readline(path);
	// print_env(tk->env);
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
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
	if (argc == 1)
	{
		tk = init_struct(env);
		init_pwd(tk);
		set_term();
		if (!tk)
			return (end_program(NULL, MALLOC));
		while (42)
		{
			set_signals(0);
			result = loop_main(tk);
			if (result == 1)
				return (d_key(&tk));
		}
	}
	else
		printf("Program requires no arguments\n");
	return (0);
}
