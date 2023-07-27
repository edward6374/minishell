/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:24:51 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/27 17:12:01 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute.h"

char	**take_double(t_env *first)
{
	int		i;
	char	**env;
	t_env	*temp;

	i = 0;
	temp = first;
	while (temp)
		((i++) && (temp = temp->next));
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	((env[i] = NULL) && (i = -1) && (temp = first));
	while (temp)
	{
		env[++i] = ft_strdup(temp->str);
		if (!env[i])
			return (free_double_char(env, i));
		temp = temp->next;
	}
	return (env);
}

static	int	is_builtin(t_min *tk, t_cmd *temp, int *p)
{
	if (!ft_strncmp("echo", temp->args[0], 5))
		return (ft_echo(temp, p));
	else if (!ft_strncmp("cd", temp->args[0], 3))
		return (ft_cd(temp));
	else if (!ft_strncmp("pwd", temp->args[0], 4))
		return (ft_pwd(temp, p));
	else if (!ft_strncmp("export", temp->args[0], 7))
		return (ft_export(tk, temp, p));
	else if (!ft_strncmp("unset", temp->args[0], 6))
		return (ft_unset(tk, temp, p));
	else if (!ft_strncmp("env", temp->args[0], 4))
		return (ft_env(tk, temp, p));
	else if (!ft_strncmp("exit", temp->args[0], 5))
		return (ft_exit(tk, temp, p));
	return (-1);
}

void	close_here_docs(t_min *tk)
{
	t_cmd	*temp;

	temp = tk->cmds;
	while (temp)
	{
		if (temp->if_here_doc)
		{
			close(temp->fd_here_doc[0]);
			close(temp->fd_here_doc[1]);
		}
		temp = temp->next;
	}
}

int	run_here_doc(t_cmd *temp, int *err)
{
	char	*string;

	if (pipe(temp->fd_here_doc) == -1)
	{
		*err = PIPE_ERROR;
		return (1);
	}
	close(temp->fd_here_doc[0]);
	while (42)
	{
		string = readline(">");
		if (!string || !ft_strncmp(string, temp->stop_word, ft_strlen(string)))
			break ;
		write(temp->fd_here_doc[1], string, ft_strlen(string));
		write(temp->fd_here_doc[1], "\n", 1);
		free(string);
	}
	if (string)
		free(string);
	return (0);
}

int	check_pipes(t_cmd *temp, int *p, int *fd)
{
//	printf("Before Pipe out: %d\tPipe in: %d\n", p[1], p[0]);
	if (temp->n == 0)
	{
		printf("First pipe\n");
		if (pipe(p) == -1)
			return (PIPE_ERROR);
	}
	if (temp->before && temp->in == 0 && temp->next)
	{
		printf("Temp before\tOld: Pipe in: %d\tPipe out: %d\n", p[0], p[1]);
		*fd = dup(p[0]);
		printf("New pipe: %d\n", *fd);
		if (*fd == -1)
		{
			perror("dup failed");
			printf("Errno: %d\n", errno);
			return (DUP_ERROR);
		}
		close(p[0]);
		close(p[1]);
		if (pipe(p) == -1)
			return (PIPE_ERROR);
		printf("Temp before\tNew: Pipe in: %d\tPipe out: %d\n", p[0], p[1]);
	}
	return (0);
}

int	loop_commands(t_min *tk, t_cmd *temp, int *p, int fd, pid_t *child_pid, int i)
{
	pid_t	pid;
	char	**env;

	printf("Number: %d\n", temp->n);
	pid = fork();
	if (pid == 0)
	{
		if (temp->in != 0)
		{
//			printf("Temp in\n");
			if (dup2(temp->in, 0) < 0 || close(temp->in) < 0 || close(p[0]))
				exit_error("dup", 1);
		}
		else
		{
			printf("Input: %d\n", fd);
			if (temp->before && temp->next)
			{
				printf("Fd: %d\n", fd);
				if (dup2(fd, 0) < 0)
					exit_error("dup", 1);
				close(fd);
			}
			else if (temp->before && !temp->next)
			{
				printf("Pipe: %d\n", fd);
				if (dup2(p[0], 0) < 0)
					exit_error("dup", 1);
			}
			if (close(p[0]) < 0)
				exit_error("close", 1);
		}
		if (temp->out != 1)
		{
			write(2, "Temp out\n", 9);
			if (dup2(temp->out, 1) < 0 || close(temp->out) < 0 || close(p[1]) < 0)
				exit_error("dup", 1);
		}
		else
		{
			write(2, "Output\n", 7);
			if (temp->next)
			{
				printf("Next exist\n");
				if (dup2(p[1], 1) < 0)
					exit_error("dup", 1);
			}
			if (close(p[1]) < 0)
				exit_error("close", 1);
		}
		env = take_double(tk->env);
		execve(temp->cmd, temp->args, env);
		exit_error("execve", 1);
//		execute_child(tk, temp, p);
	}
	child_pid[i] = pid;
	return (0);
}

int	execute_commands(t_min *tk)
{
	int			i;
	int			err;
	int			fd;
	int			status;
	int			p[2];
	pid_t		*child_pid;
	t_cmd		*temp;

	i = 0;
	fd = -1; // Serve
	p[0] = -1;
	p[1] = -1;
	child_pid = (pid_t *)malloc(sizeof(pid_t) * tk->num_cmds);
	if (!child_pid)
		return (MALLOC);
	temp = tk->cmds;
	while (temp)
	{
		if (temp->if_here_doc && run_here_doc(temp, &err))
			return (free_tokens(&tk, NULL, err));
		temp = temp->next;

	}
	temp = tk->cmds;
	while (temp)
	{
		err = check_pipes(temp, p, &fd);
		if (err)
			return (err);
		err = is_builtin(tk, temp, p);
		printf("Err: %d\n", err);
		if (err > 0)
		{
			printf("Toma:\t%d\n", err);
			exit_error((char *)g_error_array[err - 1], 1);
		}
		else if (err == -1)
		{
			if (temp->ok)
			{
				printf("Error: \t%s\n", g_error_array[temp->ok - 1]);
				temp = temp->next;
				tk->num_cmds--;
				continue ;
			}
			err = loop_commands(tk, temp, p, fd, child_pid, i);
			if (err)
				return (err);
		}
		else
			tk->num_cmds--;
		temp = temp->next;
		printf("Temp: %p\n", temp);
	}
	close(p[0]);
	close(p[1]);
	if (fd != -1)
		close(fd);
	close_here_docs(tk);
	int finished = 0;
	int	final = 0;
	while (finished < tk->num_cmds)
	{
		i = -1;
		while (++i < tk->num_cmds)
		{
			int result = waitpid(child_pid[i], &status, WNOHANG);
			if (result > 0)
			{
				finished++;
				if (i == tk->num_cmds - 1)
				{
					final = status;
					printf("Final: %d\n", final);
				}
			}
		}
	}
	printf("Status: %d\n", WEXITSTATUS(final));
	return (0);
}
