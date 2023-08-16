/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:47:54 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 19:29:11 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

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
		printf("K: %d\tI: %d\tTmp:-->%p\n", k, i, (*list));
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
	int		ret;
	char	*t1;
	char	*t2;

	if (!ft_strncmp(*tmp, "export", 7))
		return (0);
	t1 = ft_strjoin(env, "/");
	if (!t1)
		return (MALLOC + 1);
	t2 = ft_strjoin(t1, *tmp);
	if (!t2)
		return (free_pointer(t1, MALLOC + 1));
	free(t1);
	ret = check_access(t2, 1);
	if (ret)
	{
		free(t2);
		if (ret != CMD_NOT_FOUND)
			ret++;
		return (ret);
	}
	free(*tmp);
	*tmp = t2;
	return (0);
}

int	rel_path_cmd(t_min **tk, char **tmp)
{
	int		i;
	int		ret;

	i = -1;
	if ((*tmp)[0] == '.' && (*tmp)[1] == '/')
		*tmp = ft_substr(*tmp, 2, ft_strlen(*tmp) - 2);
	while ((*tk)->path[++i])
	{
		ret = join_paths(tmp, (*tk)->path[i]);
		if (!ret)
			break ;
		else if (ret == CMD_NOT_FOUND)
			continue ;
		else
			return (ret - 1);
	}
	if (!(*tk)->path[i])
		return (CMD_NOT_FOUND);
	return (0);
}

int	add_command(t_min **tk, t_parser **list, t_cmd *new)
{
	int		err;
	char	*tmp;

	err = 0;
	printf("Cmd word:--%s--\n", (*list)->word);
	tmp = ft_strdup((*list)->word);
	if (!tmp)
		return (MALLOC);
	if (tmp[0] != '/')
		err = rel_path_cmd(tk, &tmp);
	new->cmd = tmp;
	return (err);
}
