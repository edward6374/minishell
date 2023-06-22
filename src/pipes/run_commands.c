/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:24:51 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/22 19:29:09 by vduchi           ###   ########.fr       */
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
int	run_commands(t_command *token, char *env[])
{
	pid_t	pid;
	int		exit_status;
	int		status;

	printf("token->args: %s\n", token->args[0]);
	pid = fork();
	if (pid == 0)
	{
		if (dup2(token->in, 0) < 0 || dup2(token->out, 1) < 0)
		{
			perror("Error dup2");
			exit (0);
		}
		if (token->in != 0 && close(token->in) < 0)
		{
			perror("Error close input");
			exit(0);
		}
		if (token->out != 1 && close(token->out) < 0)
		{
			perror("Error close out");
			exit(0);
		}
//		if (is_cmd(token) == 0)
		execve(token->cmd, token->args, env);
		perror("Error execve");
		exit (0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			printf("Codice uscita child: %d\n", exit_status);
		}
	}
	else
	{
		perror("fork");
		return (1);
	}
//	free(token->args[0]);
	return (0);
}
