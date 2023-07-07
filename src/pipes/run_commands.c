/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:24:51 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/07 13:03:18 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

/*
char *ft_find_path(char *env[])
=======
char	*ft_find_path(char *env[])
>>>>>>> cde7f3523f81104e345425c9e4ecfc07fed347c1
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}
*/

static	int	is_builtin(char *str)
{
	if (!ft_strncmp("echo", str, 4))
		return (1);
	else if (!ft_strncmp("cd", str, 2))
		return (2);
	else if (!ft_strncmp("pwd", str, 3))
		return (3);
	else if (!ft_strncmp("export", str, 6))
		return (4);
	else if (!ft_strncmp("unset", str, 5))
		return (5);
	else if (!ft_strncmp("env", str, 3))
		return (6);
	else if (!ft_strncmp("exit", str, 4))
		return (7);
	return (0);
}

int	check_command(t_minishell *cmd)
{
	char	*str;

	str = cmd->command->args[0];
	if (is_builtin(str) == 0)
		return (0);
	return (1);
}
/*
static	int	is_cmd(t_command *token)
{
	(void)token;
	if (access("/bin/cat", F_OK | X_OK) == 0)
		return (0);
	perror("Access invalid");
	return (-1);
}
*/
int	run_commands(t_minishell *tokens, char *env[])
{
	pid_t		pid;
//	int			p1[2];
	int			status;
	t_command	*tmp;

//	printf("token->args: %s\n", token->args[0]);
	tmp = tokens->command;
	while (tmp)
	{
		if (tmp->ok)
		{
			printf("Error: ");
			end_program(NULL, tmp->ok);
			tmp = tmp->next;
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
//			if (tmp->in == 0 && tmp->before)
//			{
//				if (dup2(tmp->before->pipe[0], ) < 0)
//				{
//					perror("Error dup2 input pipe");
//					exit (0);
//				}
//				if (close(tmp->before->pipe[0]) < 0 || close(tmp->before->pipe[1]) < 0)
//				{
//					perror("Error close input pipe");
//					exit (0);
//				}
//				write(2, "Dup2 input pipe\n", 16);
//			}
//			else
//			{
//				if (dup2(tmp->in, 0) < 0)
//				{
//					perror("Error dup2 input");
//					exit (0);
//				}
//				if ((tmp->in != 0 && close(tmp->in) < 0) || close(tmp->pipe[0]) < 0)
//				{
//					perror("Error close input");
//					exit(0);
//				}
//				write(2, "Dup2 input\n", 11);
//			}
//			if (tmp->out == 1 && tmp->next)
//			{
//				if (dup2(tmp->pipe[1], 1) < 0)
//				{
//					perror("Error dup2 output pipe");
//					exit (0);
//				}
//				if (close(tmp->pipe[1]) < 0 || close(tmp->pipe[0]) < 0)
//				{
//					perror("Error close output pipe");
//					exit (0);
//				}
//				write(2, "Dup2 output pipe\n", 17);
//			}
//			else
//			{
//				if (tmp->out != 1 && dup2(tmp->out, 1) < 0)
//				{
//					perror("Error dup2 output");
//					exit (0);
//				}
//				if ((tmp->out != 1 && close(tmp->out) < 0) || close(tmp->pipe[1]) < 0)
//				{
//					perror("Error close output");
//					exit(0);
//				}
//				write(2, "Dup2 output\n", 12);
//			}
//
//			if (dup2(tmp->in, 0) < 0 || dup2(tmp->out, 1) < 0)
//			{
//				perror("Error dup2");
//				exit (0);
//			}
//
			execve(tmp->cmd, tmp->args, env);
			perror("Error execve");
			exit (0);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
			{
				tokens->exit_value = WEXITSTATUS(status);
				printf("Codice uscita child: %d\n", tokens->exit_value);
			}
		}
		else
		{
			perror("fork");
			return (1);
		}
		tmp = tmp->next;
	}
//	free(token->args[0]);
	return (0);
}
