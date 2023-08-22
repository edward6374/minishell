/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:47:54 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/22 16:11:19 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	loop_arguments(t_parser **list, t_parser **next, t_cmd *new, int k)
{
	new->args[k] = ft_strdup((*list)->word);
	if (!new->args[k])
		return (free_double_int(new->args, k));
	free((*list)->word);
	free(*list);
	*list = *next;
	if (*list)
		*next = (*list)->next;
	return (0);
}

int	add_arguments(t_parser **list, t_cmd *new)
{
	int			i;
	int			k;
	t_parser	*next;

	i = 0;
	k = -1;
	next = *list;
	while (next && ft_strncmp(next->word, "|", 2) && ++i)
		next = next->next;
	new->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new->args)
		return (MALLOC);
	next = (*list)->next;
	while (++k < i)
	{
		if (loop_arguments(list, &next, new, k))
			return (free_commands(&new, free_parser(*list, MALLOC)));
	}
	new->args[k] = NULL;
	if (*list && !ft_strncmp((*list)->word, "|", 2))
		(*list) = (*list)->next;
	return (0);
}

int	join_paths(char **tmp, char *env)
{
	int		err;
	char	*t1;
	char	*t2;

	if (!ft_strncmp(*tmp, "cd", 3) || !ft_strncmp(*tmp, "echo", 5)
		|| !ft_strncmp(*tmp, "env", 4) || !ft_strncmp(*tmp, "exit", 5)
		|| !ft_strncmp(*tmp, "export", 7) || !ft_strncmp(*tmp, "pwd", 4)
		|| !ft_strncmp(*tmp, "unset", 6))
		return (0);
	t1 = ft_strjoin(env, "/");
	if (!t1)
		return (MALLOC + 1);
	t2 = ft_strjoin(t1, *tmp);
	if (!t2)
		return (free_pointer(t1, MALLOC + 1));
	err = check_access(t1, t2, 1);
	if (err)
	{
		free(t2);
		((err != CMD_NOT_FOUND) && (++err));
		return (err);
	}
	free(*tmp);
	*tmp = t2;
	return (0);
}

int	rel_path_cmd(t_min **tk, char **tmp)
{
	int		i;
	int		err;
	char	**path;

	path = path_env((*tk)->env);
	i = -1;
	if ((*tmp)[0] == '.' && (*tmp)[1] == '/')
	{
		ft_free_dptr(path);
		return (check_access(NULL, (*tmp), 1));
	}
	while (path[++i])
	{
		err = join_paths(tmp, path[i]);
		if (!err)
			break ;
		else if (err == CMD_NOT_FOUND)
			continue ;
		else
			return (err - 1);
	}
	if (!path[i])
		return (CMD_NOT_FOUND);
	ft_free_dptr(path);
	return (0);
}

int	add_command(t_min **tk, t_parser **list, t_cmd *new)
{
	int		err;
	char	*tmp;

	err = 0;
	tmp = ft_strdup((*list)->word);
	if (!tmp)
		return (MALLOC);
	if (tmp[0] != '/')
		err = rel_path_cmd(tk, &tmp);
	new->cmd = tmp;
	return (err);
}
