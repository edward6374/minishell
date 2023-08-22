/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:10:16 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/22 20:32:04 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"
#include "execute.h"
#include "minishell.h"

void set_g(t_min *tk, int ok)
{
	printf("OK: %d\n", ok);
	if (ok == 6)
		g_exit = 127;
	else if (ok == 7)
		g_exit = 126;
	else
		g_exit = 1;
	tk->num_cmds = tk->num_cmds - 1;
}

void	end_exec(t_min *tk, pid_t *child_pid, char **env)
{
	int	final;
	int	status;
	int	finished;

	final = 0;
	status = 0;
	finished = 0;
	while (finished < tk->num_cmds)
	{
		if (waitpid(-1, &status, 0) == child_pid[tk->num_cmds - 1])
			final = status;
		g_exit = WEXITSTATUS(final);
		finished++;
	}
	// g_exit = WEXITSTATUS(final);
	printf(BLUE "Exit: %d\n", g_exit);
	if (child_pid)
		free(child_pid);
	free_double_void(env);
}

int	is_builtin(t_min *tk, t_cmd *tmp, int p)
{
	if (!ft_strncmp("echo", tmp->cmd, 5))
		return (ft_echo(tmp, tmp->args, p));
	else if (!ft_strncmp("cd", tmp->cmd, 3))
		return (ft_cd(tmp->args, tk->env));
	else if (!ft_strncmp("pwd", tmp->cmd, 4))
		return (ft_pwd(tmp, p));
	else if (!ft_strncmp("export", tmp->cmd, 7))
		return (ft_export(tk, tmp, p));
	else if (!ft_strncmp("unset", tmp->cmd, 6))
		return (ft_unset(tk, tmp));
	else if (!ft_strncmp("env", tmp->cmd, 4))
		return (ft_env(tk, tmp, p));
	else if (!ft_strncmp("exit", tmp->cmd, 5))
		return (ft_exit(tmp));
	return (-1);
}

char	**take_double(t_env *first)
{
	int		i;
	t_env	*tmp;
	char	**env;

	i = 0;
	env = NULL;
	tmp = first;
	while (tmp && ++i)
		tmp = tmp->next;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	tmp = first;
	while (tmp)
	{
		if (!tmp->value)
			env[i] = ft_strjoin(tmp->name, "");
		else
			env[i] = ft_strjoin(tmp->name, tmp->value);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
