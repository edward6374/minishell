/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:10:16 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/29 15:46:42 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "execute.h"
#include "minishell.h"

void	set_g(t_min *tk, int ok)
{
	if (ok == 6)
		g_exit = 127;
	else if (ok == 7)
		g_exit = 126;
	else
		g_exit = 1;
	tk->num_cmds = tk->num_cmds - 1;
}

void	take_more_exit(char **str, int i)
{
	int		j;
	char	*last;

	j = 1;
	last = ft_strdup(ft_itoa(g_exit));
	while (str[i][++j])
	{
		if (str[i][j] == '$' && str[i][j + 1] == '?')
			((last = ft_strjoin(last, ft_strdup(ft_itoa(g_exit)))) && (++j));
		else if (ft_strchr(str[i] + j, '$'))
		{
			last = ft_strjoin(last, ft_substr(str[i], j, ft_strchr(str[i] + j,
						'$') - &str[i][j]));
			j += ft_strchr(str[i] + j, '$') - &str[i][j] - 1;
		}
		else if (!ft_strchr(str[i] + j, '$'))
		{
			last = ft_strjoin(last, ft_substr(str[i], j, ft_strlen(str[i])
					- j));
			break ;
		}
	}
	free(str[i]);
	str[i] = ft_strdup(last);
	free(last);
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
		if (!WIFSIGNALED(status))
			g_exit = WEXITSTATUS(status);
		finished++;
	}
	if (child_pid)
		free(child_pid);
	free_double_void(env);
}

int	run_builtin(t_min *tk, t_cmd *tmp, pid_t *child_pid)
{
	if (tk->num_cmds == 1)
	{
		take_exit_value(tmp);
		free_double_void(tk->pt_env);
		if (child_pid)
			free(child_pid);
	}
	if (!ft_strncmp("echo", tmp->cmd, 5))
		return (ft_echo(tmp->args, 1));
	else if (!ft_strncmp("cd", tmp->cmd, 3))
		return (ft_cd(tmp->args, tk));
	else if (!ft_strncmp("pwd", tmp->cmd, 4))
		return (ft_pwd());
	else if (!ft_strncmp("export", tmp->cmd, 7))
		return (ft_export(tk, tmp));
	else if (!ft_strncmp("unset", tmp->cmd, 6))
		return (ft_unset(tk, tmp));
	else if (!ft_strncmp("env", tmp->cmd, 4))
		return (ft_env(tk));
	return (ft_exit(tmp));
}

char	**take_double(t_min *tk, t_env *first)
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
			env[i++] = ft_strjoin(tmp->name, "");
		else
			env[i++] = ft_strjoin(tmp->name, tmp->value);
		tmp = tmp->next;
	}
	env[i] = NULL;
	tk->pt_env = env;
	return (env);
}
