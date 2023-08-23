/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_hdoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:23:00 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/23 22:36:11 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

void	check_temp_fd(t_cmd *tmp, int *p, int *fd)
{
	if (tmp->n == 0 && tmp->next)
		pipe(p);
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
