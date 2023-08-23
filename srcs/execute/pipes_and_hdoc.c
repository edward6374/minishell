/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_hdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:23:00 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/23 11:22:32 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "signalm.h"

void	close_here_doc(t_min *tk)
{
	t_cmd	*tmp;

	tmp = tk->cmds;
	while (tmp)
	{
		if (tmp->hdoc->yes)
		{
			close(tmp->hdoc->fd[0]);
			close(tmp->hdoc->fd[1]);
		}
		tmp = tmp->next;
	}
}

void	close_all_pipes(t_min *tk, int *p, int fd)
{
	close_here_doc(tk);
	close(p[0]);
	close(p[1]);
	if (fd != -1)
		close(fd);
}

void	run_here_doc(t_cmd *tmp)
{
	char	*line;

	if (!tmp->hdoc->yes)
		return ;
	set_signals(HEREDOC);
	pipe(tmp->hdoc->fd);
	while (42)
	{
		line = readline("> ");
		if (!ft_strncmp(line, tmp->hdoc->stop, ft_strlen(line)))
			break ;
		ft_putstr_fd(line, tmp->hdoc->fd[1]);
		ft_putchar_fd('\n', tmp->hdoc->fd[1]);
		free(line);
		line = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
}

void	check_temp_fd(t_cmd *tmp, int *p, int *fd)
{
	if (tmp->n == 0 && tmp->next)
	{
		// printf("First pipe\n");
		pipe(p);
	}
	else if (tmp->before && tmp->in_fd == 0 && tmp->next && !tmp->hdoc->yes)
	{
		*fd = dup(p[0]);
		close(p[0]);
		close(p[1]);
		pipe(p);
	}
}

void	redirect_pipes(t_cmd *tmp, int *p, int fd)
{
	if (tmp->in_fd != 0 && !tmp->hdoc->first)
	{
		// printf("In fd\n");
		((dup2(tmp->in_fd, 0)) && (close(tmp->in_fd)));
	}
	else
	{
		// printf("In\n");
		if (tmp->hdoc->yes)
		{
			// printf("In here_doc\n");
			dup2(tmp->hdoc->fd[0], 0);
			((close(tmp->hdoc->fd[0])) && (close(tmp->hdoc->fd[1])));
		}
		else if (tmp->before && tmp->next)
		{
			// printf("In fd\n");
			((dup2(fd, 0)) && (close(fd)));
		}
		else if (tmp->before && !tmp->next)
		{
			// printf("In pipe\n");
			dup2(p[0], 0);
		}
	}
	close(p[0]);
	if (tmp->out_fd != 1)
	{
		// printf("Out\n");
		((dup2(tmp->out_fd, 1)) && (close(tmp->out_fd)));
	}
	else if (tmp->out_fd == 1 && tmp->next)
	{
		// printf("Out pipe\n");
		dup2(p[1], 1);
	}
	close(p[1]);
}
