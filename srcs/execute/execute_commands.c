/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:24:51 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/21 21:40:31 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/execute.h"

void	close_here_docs(t_minishell *tokens)
{
	t_command	*temp;

	temp = tokens->command;
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

void	exit_error(char *str, int i)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(i);
}

int	run_here_doc(t_command *temp, int *err)
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

int	check_pipes(t_command *temp, int *p, int *fd)
{
	int		test;

	test = -1;
	printf("Before Pipe out: %d\tPipe in: %d\n", p[1], p[0]);
	if (temp->n == 0 && pipe(p) == -1)
	{
		printf("First pipe\n");
		return (PIPE_ERROR);
	}
	if (temp->before && temp->in == 0)
	{
		close(p[1]);
		printf("After Pipe out: %d\tPipe in: %d\n", p[1], p[0]);
		test = dup(1);
		printf("New pipe: %d\n", test);
		if (test == -1)
		{
			perror("dup failed");
			printf("Errno: %d\n", errno);
			return (DUP_ERROR);
		}
		close(p[0]);
		if (pipe(p) == -1)
			return (PIPE_ERROR);
//		data = (char *)malloc(sizeof(char));
//		if (!data)
//			return (MALLOC);
//		while (read(fd, data, 1) > 0)
//			write(p[1], data, 1);
//		close(fd);
	}
	*fd = test;
	return (0);
}

int	loop_commands(t_minishell *tokens, t_command *temp, int *p, int fd)
{
	int		status;
//	char	*data;
	pid_t	pid;

	printf("Number: %d\n", temp->n);
//	printf("Before Pipe out: %d\tPipe in: %d\n", p[1], p[0]);
//	if (temp->n == 0 && pipe(p) == -1)
//	{
//		printf("First pipe\n");
//		return (PIPE_ERROR);
//	}
//	printf("After Pipe out: %d\tPipe in: %d\n", p[1], p[0]);
//	if (temp->before && temp->in == 0)
//	{
//		close(p[1]);
//		fd = dup2(p[0], 127);
//		printf("New pipe: %d\n", fd);
//		if (fd == -1)
//			return (DUP_ERROR);
//		close(p[0]);
//		if (pipe(p) == -1)
//			return (PIPE_ERROR);
//		data = (char *)malloc(sizeof(char));
//		if (!data)
//			return (MALLOC);
//		while (read(fd, data, 1) > 0)
//			write(p[1], data, 1);
//		close(fd);
//	}
	pid = fork();
	if (pid == 0)
	{
		if (temp->ok)
			exit_error((char *)g_error_array[temp->ok - 1], temp->ok);
		if (temp->in != 0)
		{
			if (dup2(temp->in, 0) < 0 || close(temp->in) < 0 || close(p[0]))
				exit_error("dup", 1);
			printf("Temp in\n");
		}
		else if (temp->in == 0)
		{
			if (temp->before)
			{
				printf("Before exist\n");
				if (dup2(fd, 0) < 0)
					exit_error("dup", 1);
				close(fd);
			}
			if (close(p[0]) < 0)
				exit_error("close", 1);
			printf("Input\n");
		}
		if (temp->out != 1)
		{
			if (dup2(temp->out, 1) < 0 || close(temp->out) < 0 || close(p[1]) < 0)
				exit_error("dup", 1);
			write(2, "Temp out\n", 9);
//			printf("Temp out\n")
		}
		else if (temp->out == 1)
		{
			if (temp->next)
			{
				printf("Next exist\n");
				if (dup2(p[1], 1) < 0)
					exit_error("dup", 1);
			}
			if (close(p[1]) < 0)
				exit_error("close", 1);
			write(2, "Output\n", 7);
//			printf("Output\n");
		}
		execve(temp->cmd, temp->args, tokens->env);
		exit_error("execve", 1);
//		execute_child(tokens, temp, p);
	}
	else
	{
		close(p[0]);
		close(p[1]);
		if (temp->before && temp->in == 0)
			close(fd);
		close_here_docs(tokens);
		waitpid(-1, &status, 0);
	}
	return (0);
}

int	execute_commands(t_minishell *tokens)
{
	int			err;
	int			fd;
	int			pipe[2];
	t_command	*temp;

	temp = tokens->command;
	while (temp)
	{
		if (temp->if_here_doc && run_here_doc(temp, &err))
			return (free_tokens(&tokens, NULL, err));
		temp = temp->next;
	}
	temp = tokens->command;
	while (temp)
	{
		err = check_pipes(temp, pipe, &fd);
		if (err)
			return (err);
		err = loop_commands(tokens, temp, pipe, fd);
		if (err)
			return (err);
		temp = temp->next;
	}
	return (0);
}

/*
static	int	is_builtin(char *str)
{
	if (!ft_strncmp("echo", str, 4))
		return (1);
	else if (!ft_strncmp("cd", str, 2))
		return (2);
	else if (!ft_strncmp("pwd", str, 3))
		return (3);
	else if (!ft_strncmp("export", str, 6))
		return (4);
	else if (!ft_strncmp("unset", str, 5))
		return (5);
	else if (!ft_strncmp("env", str, 3))
		return (6);
	else if (!ft_strncmp("exit", str, 4))
		return (7);
	return (0);
}
*/
/*
int	run_commands(t_minishell *tokens, char *env[])
{
	pid_t		pid;
//	int			p1[2];
	int			status;
	t_command	*tmp;

//	printf("token->args: %s\n", token->args[0]);
	tmp = tokens->command;
	while (tmp)
	{
		if (tmp->ok)
		{
			printf("Error: ");
			end_program(NULL, tmp->ok);
			tmp = tmp->next;
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
//			if (tmp->in == 0 && tmp->before)
//			{
//				if (dup2(tmp->before->pipe[0], ) < 0)
//				{
//					perror("Error dup2 input pipe");
//					exit (0);
//				}
//				if (close(tmp->before->pipe[0]) < 0 || close(tmp->before->pipe[1]) < 0)
//				{
//					perror("Error close input pipe");
//					exit (0);
//				}
//				write(2, "Dup2 input pipe\n", 16);
//			}
//			else
//			{
//				if (dup2(tmp->in, 0) < 0)
//				{
//					perror("Error dup2 input");
//					exit (0);
//				}
//				if ((tmp->in != 0 && close(tmp->in) < 0) || close(tmp->pipe[0]) < 0)
//				{
//					perror("Error close input");
//					exit(0);
//				}
//				write(2, "Dup2 input\n", 11);
//			}
//			if (tmp->out == 1 && tmp->next)
//			{
//				if (dup2(tmp->pipe[1], 1) < 0)
//				{
//					perror("Error dup2 output pipe");
//					exit (0);
//				}
//				if (close(tmp->pipe[1]) < 0 || close(tmp->pipe[0]) < 0)
//				{
//					perror("Error close output pipe");
//					exit (0);
//				}
//				write(2, "Dup2 output pipe\n", 17);
//			}
//			else
//			{
//				if (tmp->out != 1 && dup2(tmp->out, 1) < 0)
//				{
//					perror("Error dup2 output");
//					exit (0);
//				}
//				if ((tmp->out != 1 && close(tmp->out) < 0) || close(tmp->pipe[1]) < 0)
//				{
//					perror("Error close output");
//					exit(0);
//				}
//				write(2, "Dup2 output\n", 12);
//			}
//
//			if (dup2(tmp->in, 0) < 0 || dup2(tmp->out, 1) < 0)
//			{
//				perror("Error dup2");
//				exit (0);
//			}
//
			execve(tmp->cmd, tmp->args, env);
			perror("Error execve");
			exit (0);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				tokens->exit_value = WEXITSTATUS(status);
				printf("Codice uscita child: %d\n", tokens->exit_value);
			}
		}
		else
		{
			perror("fork");
			return (1);
		}
		tmp = tmp->next;
	}
//	free(token->args[0]);
	return (0);
}
*/
