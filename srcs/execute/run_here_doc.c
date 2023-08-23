/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:34:31 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/23 23:04:22 by nmota-bu         ###   ########.fr       */
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
