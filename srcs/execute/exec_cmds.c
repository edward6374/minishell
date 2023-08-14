/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:24:51 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/14 10:50:37 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "execute.h"

void	close_all_pipes(t_min *tk, int *p, int fd)
{
	t_cmd	*tmp;

	tmp = tk->cmds;
	while (tmp)
	{
		if (tmp->here_doc->if_hdoc)
		{
			close(tmp->here_doc->fd_hdoc[0]);
			close(tmp->here_doc->fd_hdoc[1]);
		}
		tmp = tmp->next;
	}
	close(p[0]);
	close(p[1]);
	if (fd != -1)
		close(fd);
}

int	run_here_doc(t_cmd *tmp)
{
	char	*string;

	if (!tmp->here_doc->if_hdoc)
		return (0);
	if (pipe(tmp->here_doc->fd_hdoc) == -1)
		return (PIPE_ERROR);
	close(tmp->here_doc->fd_hdoc[0]);
	while (42)
	{
		string = readline(">");
		if (!ft_strncmp(string, tmp->here_doc->stop_word, ft_strlen(string)))
			break ;
		write(tmp->here_doc->fd_hdoc[1], string, ft_strlen(string));
		write(tmp->here_doc->fd_hdoc[1], "\n", 1);
		free(string);
		string = NULL;
	}
	printf("\033[38;5;209mRun here doc\n\033[0;0m");
	if (string)
		free(string);
	return (0);
}

int	check_temp_fd(t_cmd *tmp, int *p, int *fd)
{
	if (tmp->n == 0)
	{
		if (pipe(p) == -1)
			return (PIPE_ERROR);
		printf("First pipe\n\n");
	}
	if (tmp->before && tmp->in_fd == 0 && tmp->next)
	{
		*fd = dup(p[0]);
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
		printf("Temp before\tNew: Pipe in: %d\tPipe out: %d\n\n", p[0], p[1]);
	}
	return (0);
}

/* // NO BORRAR, esta es la version pequena, sin comentarios ni write
void	redirect_pipes(t_cmd *tmp, int *p, int fd)
{
	if (tmp->in_fd != 0)
		((dup2(tmp->in_fd, 0)) && (close(tmp->in_fd)));
	else
	{
		if (tmp->before && tmp->next)
			((dup2(fd, 0)) && (close(fd)));
		else if (tmp->before && !tmp->next)
			dup2(p[0], 0);
	}
	close(p[0]);
	if (tmp->out_fd != 1)
		((dup2(tmp->out_fd, 0)) && (close(tmp->out_fd)));
	else
		((tmp->next) && (dup2(p[1], 1)));
	close(p[1]);
}
*/

void	redirect_pipes(t_cmd *tmp, int *p, int fd)
{
	printf("Pipes redirections\n");
	if (tmp->in_fd != 0)
	{
		write(2, "Temp in\t", 8);
		if (dup2(tmp->in_fd, 0) < 0)
			exit_error("dup_in", 1);
		close(tmp->in_fd);
	}
	else
	{
		write(2, "Input\t", 6);
		if (tmp->before && tmp->next)
		{
			write(2, "Fd\t", 3);
			if (dup2(fd, 0) < 0)
				exit_error("dup_fd", 1);
			close(fd);
		}
		else if (tmp->before && !tmp->next)
		{
			write(2, "Pipe input\t", 11);
			if (dup2(p[0], 0) < 0)
				exit_error("dup_pipe", 1);
		}
	}
	write(2, "Close input\n", 12);
	close(p[0]);
	if (tmp->out_fd != 1)
	{
		write(2, "Temp out\t", 9);
		if (dup2(tmp->out_fd, 0) < 0)
			exit_error("dup_in", 1);
		close(tmp->out_fd);
	}
	else
	{
		write(2, "Output\t", 7);
		if (tmp->next)
		{
			write(2, "Pipe output\t", 12);
			if (dup2(p[1], 1) < 0)
				exit_error("dup_pipe", 1);
		}
	}
	write(2, "Close output\n\n", 14);
	close(p[1]);
}

int	check_before_exec(t_min *tk, t_cmd *tmp, int *p, int *fd)
{
	int	err;

	err = check_temp_fd(tmp, p, fd); //Es por el dup error y el pipe error -> borrar
	if (err)
		return (err);
	err = is_builtin(tk, tmp, p[1]); //Todo esto hay que activarlo cuando se trabaja con los built-ins
	if (err > 0)
		exit_error((char *)g_error_array[err - 1], 1);
	else if (err == -1)
	{
		if (tmp->ok)
		{
			printf("Error: \t%s\n", g_error_array[tmp->ok - 1]);
			tk->num_cmds--;
		}
		return (0);
	}
	else
		tk->num_cmds--;
	return (-1);
}

void	child(t_cmd *tmp, char **env, int *p, int fd)
{
	redirect_pipes(tmp, p, fd);
	printf("\033[0;39mChild\n");
	execve(tmp->cmd, tmp->args, env);
}

int	loop_commands(t_min *tk, pid_t *child_pid, int *p, int fd)
{
	int		err;
	pid_t	pid;
	t_cmd	*tmp;
	char	**env;

	env = take_double(tk->env);
	if (!env)
		return (MALLOC);
	tmp = tk->cmds;
	while (tmp)
	{
		err = check_before_exec(tk, tmp, p, &fd);
		if (err == -1)
		{
			tmp = tmp->next;
			continue ;
		}
		pid = fork();
		if (pid == 0)
			child(tmp, env, p, fd);
		*child_pid = pid;
		tmp = tmp->next;
	}
	close_all_pipes(tk, p, fd);
	end_exec(tk, child_pid, env);
	return (0);
}

int	execute_commands(t_min *tk)
{
	int			fd;
	int			err;
	int			p[2];
	t_cmd		*tmp;
	pid_t		*child_pid;

	fd = -1;
	p[0] = -1;
	p[1] = -1;
	child_pid = (pid_t *)malloc(sizeof(pid_t) * tk->num_cmds);
	if (!child_pid)
		return (MALLOC);
	tmp = tk->cmds;
	while (tmp)
	{
		if (run_here_doc(tmp))
			return (free_all(tk, PIPE_ERROR));
		tmp = tmp->next;
	}
	err = loop_commands(tk, child_pid, p, fd);
	if (err == MALLOC)
		return (free_all(tk, MALLOC));
	return (0);
}
