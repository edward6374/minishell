/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:24:51 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/22 11:01:04 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "execute.h"

int	check_before_exec(t_min *tk, t_cmd **tmp, int *p, int *fd)
{
	int	res;

	check_temp_fd(*tmp, p, fd);
	if ((*tmp)->ok)
	{
		if ((*tmp)->err_f)
			printf("minishell: %s: %s\n", (*tmp)->err_f, g_error_array[(*tmp)->ok - 1]);
		else
			printf("minishell: %s: %s\n", (*tmp)->cmd, g_error_array[(*tmp)->ok - 1]);
		tk->num_cmds--;
		*tmp = (*tmp)->next;
		return (-1);
	}
	res = is_builtin(tk, *tmp, p[1]);
	if (res >= 0)
	{
		tk->num_cmds--;
		*tmp = (*tmp)->next;
	}
	else
		return (0);
	return (-1);
}

int	loop_commands(t_min *tk, pid_t *child_pid, int *p, int fd)
{
	pid_t	pid;
	t_cmd	*tmp;
	char	**env;

	env = take_double(tk->env);
	if (!env)
		return (MALLOC);
	tmp = tk->cmds;
	while (tmp)
	{
		if (check_before_exec(tk, &tmp, p, &fd) == -1)
			continue ;
		pid = fork();
		if (pid == 0)
		{
			set_signals(tk, INTERACT);
//			signal(SIGQUIT, siginthandler);
			redirect_pipes(tmp, p, fd);
			close_here_doc(tk);
			execve(tmp->cmd, tmp->args, env);
		}
		*child_pid = pid;
		tmp = tmp->next;
	}
	close_all_pipes(tk, p, fd);
	end_exec(tk, child_pid, env);
	return (0);
}

int	execute_commands(t_min *tk)
{
	int		fd;
	int		p[2];
	int		err;
	t_cmd	*tmp;
	pid_t	*child_pid;

	fd = -1;
	p[0] = -1;
	p[1] = -1;
	child_pid = (pid_t *)malloc(sizeof(pid_t) * tk->num_cmds);
	if (!child_pid)
		return (MALLOC);
	tmp = tk->cmds;
	while (tmp)
	{
		run_here_doc(tmp);
		tmp = tmp->next;
	}
	err = loop_commands(tk, child_pid, p, fd);
	if (err == MALLOC)
		return (free_all(tk, MALLOC));
	return (0);
}
