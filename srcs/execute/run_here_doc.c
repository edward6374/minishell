/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:34:31 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/23 22:49:55 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "signalm.h"

void static	print_line(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	free(line);
	line = NULL;
}

void static	end_run(int *status, pid_t pid)
{
	waitpid(pid, status, 0);
	printf("");
	g_exit = WEXITSTATUS(status);
}

void	run_here_doc(t_cmd *tmp)
{
	t_run	run;

	// int		status;
	// pid_t	pid;
	// char	*line;
	if (!tmp->hdoc->yes)
		return ;
	pipe(tmp->hdoc->fd);
	set_signals(3);
	run.pid = fork();
	if (run.pid == 0)
	{
		set_signals(2);
		while (42)
		{
			run.line = readline("> ");
			if (!run.line || (run.line[0] != '\0' && !ft_strncmp(run.line,
						tmp->hdoc->stop, ft_strlen(run.line))))
				break ;
			print_line(run.line, tmp->hdoc->fd[1]);
			// ft_putstr_fd(line, tmp->hdoc->fd[1]);
			// ft_putchar_fd('\n', tmp->hdoc->fd[1]);
			// free(line);
			// line = NULL;
		}
		if (run.line)
		{
			free(run.line);
			run.line = NULL;
		}
		exit(0);
	}
	end_run(&run.status, run.pid);
	// waitpid(pid, &status, 0);
	// printf("");
	// g_exit = WEXITSTATUS(status);
}
