/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_hdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:23:00 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/30 12:06:18 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	one_builtin(t_min *tk, t_cmd *tmp, pid_t *child_pid)
{
	int	out_tmp;

	out_tmp = -1;
	if (check_before_exec(tk, &tmp, NULL, NULL) == -1)
		return ;
	if (tmp->out_fd != 1)
	{
		out_tmp = dup(1);
		dup2(tmp->out_fd, 1);
		close(tmp->out_fd);
	}
	take_exit_value(tmp);
	free_double_void(tk->pt_env);
	if (child_pid)
		free(child_pid);
	g_exit = run_builtin(tk, tmp);
	if (out_tmp != -1)
	{
		dup2(out_tmp, 1);
		close(out_tmp);
	}
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "exit", 5)
		|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}

void	close_all_pipes(t_min *tk, int *p, int fd)
{
	close_here_doc(tk);
	close(p[0]);
	close(p[1]);
	if (fd != -1)
		close(fd);
}

void	check_temp_fd(t_cmd *tmp, int *p, int *fd)
{
	if (tmp->n == 0 && tmp->next)
		pipe(p);
	else if (tmp->before && tmp->in_fd == 0 && tmp->next && !tmp->hdoc->yes)
	{
		if (*fd != -1)
			close(*fd);
		*fd = dup(p[0]);
		close(p[0]);
		close(p[1]);
		pipe(p);
	}
}

void	redirect_pipes(t_cmd *tmp, int *p, int fd)
{
	if (tmp->in_fd != 0 && !tmp->hdoc->first)
		((dup2(tmp->in_fd, 0)) && (close(tmp->in_fd)));
	else
	{
		if (tmp->hdoc->yes)
		{
			dup2(tmp->hdoc->fd[0], 0);
			((close(tmp->hdoc->fd[0])) && (close(tmp->hdoc->fd[1])));
		}
		else if (tmp->before && tmp->next)
			((dup2(fd, 0)) && (close(fd)));
		else if (tmp->before && !tmp->next)
			dup2(p[0], 0);
	}
	close(p[0]);
	if (tmp->out_fd != 1)
		((dup2(tmp->out_fd, 1)) && (close(tmp->out_fd)));
	else if (tmp->out_fd == 1 && tmp->next)
		dup2(p[1], 1);
	close(p[1]);
}
