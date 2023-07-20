/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:00:14 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/16 15:03:10 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "readline/library/include/readline/readline.h"
#include "readline/library/include/readline/history.h"

int main(int argc, char **argv, char *env[])
{
	int		p[2];
	int		status;
	pid_t	pid;
	char	*string;
	char	*cmd;
	char	**args;

	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		while (42)
		{
			string = readline("test> ");
			printf("Res: --%s--\n", string);
			if (!string || !ft_strncmp(string, "here", 5))
				break ;
			write(p[1], string, ft_strlen(string));
			write(p[1], "\n", 1);
			free(string);
		}
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		printf("Father\n");
		cmd = ft_strdup("/bin/cat");
		args = malloc(sizeof(char *) * 2);
		args[0] = ft_strdup("cat");
		args[1] = NULL;
		execve(cmd, args, env);
	}
}
