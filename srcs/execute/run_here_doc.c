/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:34:31 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/24 11:44:09 by vduchi           ###   ########.fr       */
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

size_t static	l(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int static	ncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 != '\0' && *s1 == *s2 && n > 1)
	{
		s1++;
		s2++;
		n--;
	}
	return (((unsigned char)*s1) - ((unsigned char)*s2));
}

void	run_here_doc(t_cmd *tmp)
{
	t_run	r;

	if (!tmp->hdoc->yes)
		return ;
	pipe(tmp->hdoc->fd);
	set_signals(3);
	r.pid = fork();
	if (r.pid == 0)
	{
		set_signals(2);
		while (42)
		{
			r.l = readline("> ");
			if (!r.l || (r.l[0] != '\0' && !ncmp(r.l, tmp->hdoc->stop, l(r.l))))
				break ;
			print_line(r.l, tmp->hdoc->fd[1]);
		}
		if (r.l)
		{
			free(r.l);
			r.l = NULL;
		}
		exit(0);
	}
	end_run(&r.status, r.pid);
}

// void	run_here_doc(t_cmd *tmp)
// {
// 	int status;
// 	pid_t pid;
// 	char	*line;

// 	if (!tmp->hdoc->yes)
// 		return;
// 	pipe(tmp->hdoc->fd);
// 	set_signals(3);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		child_
// 		set_signals(2);
// 		while (42)
// 		{
// 			line = readline("> ");
// 			if (!line || (line[0] != '\0' && !ft_strncmp(line, tmp->hdoc->stop, ft_strlen(line))))
// 				break;
// 			ft_putstr_fd(line, tmp->hdoc->fd[1]);
// 			ft_putchar_fd('\n', tmp->hdoc->fd[1]);
// 			free(line);
// 			line = NULL;
// 		}
// 		if (line)
// 		{
// 			free(line);
// 			line = NULL;
// 		}
// 		exit(0);
// 	}
// 	waitpid(pid, &status, 0);
// 	printf("");
// 	g_exit = WEXITSTATUS(status);
// }
