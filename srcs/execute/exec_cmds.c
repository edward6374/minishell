/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:24:51 by vduchi            #+#    #+#             */
/*   Updated: 2023/09/02 10:57:22 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"
#include "signalm.h"
#include <errno.h>

int	check_before_exec(t_min *tk, t_cmd **tmp, int *p, int *fd)
{
	check_temp_fd(*tmp, p, fd);
	if ((*tmp)->ok)
	{
		if ((*tmp)->err_f)
			printf("%s %s: %s\n", TERROR, (*tmp)->err_f,
				g_error_array[(*tmp)->ok - 1]);
		else
			printf("%s %s: %s\n", TERROR, (*tmp)->cmd, g_error_array[(*tmp)->ok
				- 1]);
		set_g(tk, (*tmp)->ok);
		*tmp = (*tmp)->next;
		return (-1);
	}
	return (0);
}

void	take_exit_value(t_cmd *tmp)
{
	int	i;

	i = 0;
	while (tmp->args[++i])
	{
		if (!ft_strncmp(tmp->args[i], "$?", 3))
		{
			free(tmp->args[i]);
			tmp->args[i] = ft_strdup(ft_itoa(g_exit));
		}
		else if (!ft_strncmp(tmp->args[i], "$?", 2))
			take_more_exit(tmp->args, i);
	}
	g_exit = 0;
}

pid_t static child_exec(t_min *tk, t_cmd *tmp, int *p, int fd)
{
	pid_t	pid;

	set_signals(1);
	pid = fork();
	if (pid == 0)
	{
		redirect_pipes(tmp, p, fd);
		close_here_doc(tk);
		if (is_builtin(tmp->cmd))
		{
			g_exit = run_builtin(tk, tmp);
			exit(g_exit);
		}
		else
			execve(tmp->cmd, tmp->args, tk->pt_env);
	}
	return (pid);
}

int	loop_commands(t_min *tk, pid_t *child_pid, int *p, int fd)
{
	t_cmd	*tmp;
	char	**env;

	env = take_double(tk, tk->env);
	if (!env)
		return (MALLOC);
	tmp = tk->cmds;
	if (!tmp)
		return (0);
	if (tk->num_cmds == 1 && is_builtin(tk->cmds->cmd))
		one_builtin(tk, tk->cmds, child_pid);
	else
	{
		while (tmp)
		{
			take_exit_value(tmp);
			if (check_before_exec(tk, &tmp, p, &fd) == -1)
				continue ;
			*child_pid = child_exec(tk, tmp, p, fd);
			tmp = tmp->next;
		}
		close_all_pipes(tk, p, fd);
		end_exec(tk, child_pid, env);
	}
	return (0);
}

int	execute_commands(t_min *tk)
{
	int		fd;
	int		p[2];
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
	if (loop_commands(tk, child_pid, p, fd))
		return (free_all(tk, MALLOC));
	return (0);
}
