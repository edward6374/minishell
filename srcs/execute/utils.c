/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:10:16 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/12 13:28:24 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "built-ins.h"

void end_exec(t_min *tk, pid_t *child_pid, char **env)
{
	int	final;
	int	status;
	int finished;

	final = 0;
	status = 0;
	finished = 0;
	while (finished < tk->num_cmds)
	{
		if (waitpid(-1, &status, 0) == child_pid[tk->num_cmds - 1]) // Te lo explico manana
		{
			final = status;
			printf("Final: %d\n", final);
		}
		finished++;
	}
	printf("Status: %d\n", WEXITSTATUS(final));
	tk->exit_value = WEXITSTATUS(final);
	if (child_pid)
		free(child_pid);
	free_double_void(env);
}

int	is_builtin(t_min *tk, t_cmd *tmp, int p)
{
	if (!ft_strncmp("echo", tmp->args[0], 5))
		return (ft_echo(tmp, p));
	else if (!ft_strncmp("cd", tmp->args[0], 3))
		return (ft_cd(tmp));
	else if (!ft_strncmp("pwd", tmp->args[0], 4))
		return (ft_pwd(tmp, p));
	else if (!ft_strncmp("export", tmp->args[0], 7))
		return (ft_export(tk, tmp, p));
	else if (!ft_strncmp("unset", tmp->args[0], 6))
		return (ft_unset(tk, tmp));
	else if (!ft_strncmp("env", tmp->args[0], 4))
		return (ft_env(tk, tmp, p));
	else if (!ft_strncmp("exit", tmp->args[0], 5))
		return (ft_exit(tk, tmp));
	return (-1);
}

char	**take_double(t_env *first)
{
	int		i;
	char	**env;
	t_env	*tmp;

	i = 0;
	tmp = first;
	while (tmp && ++i)
		tmp = tmp->next;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = -1;
	tmp = first;
	while (tmp)
	{
		if (!tmp->value)
			env[++i] = ft_strjoin(tmp->name, "");
		else
			env[++i] = ft_strjoin(tmp->name, tmp->value);
		if (!env[i])
			return (free_double_char(env, i));
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
