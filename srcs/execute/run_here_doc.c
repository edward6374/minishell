/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:34:31 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/24 12:30:46 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "signalm.h"

void	run_loop(t_cmd *tmp, char *line)
{
	set_signals(2);
	while (42)
	{
		line = readline("> ");
		if (!line || (line[0] != '\0' && !ft_strncmp(line, tmp->hdoc->stop,
					ft_strlen(line))))
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
	exit(0);
}

void	run_here_doc(t_cmd *tmp)
{
	int		status;
	pid_t	pid;
	char	*line;

	line = NULL;
	if (!tmp->hdoc->yes)
		return ;
	pipe(tmp->hdoc->fd);
	set_signals(3);
	pid = fork();
	if (pid == 0)
		run_loop(tmp, line);
	waitpid(pid, &status, 0);
	printf("");
	g_exit = WEXITSTATUS(status);
}
