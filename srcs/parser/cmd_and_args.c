/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:47:54 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/11 11:18:11 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

int	check_access(char *str, int mode)
{
	if (mode == 1)
	{
		if (access(str, X_OK) == 0)
			return (0);
		if (access(str, F_OK) == 0)
			return (CMD_FOUND_NOT_EX);
		return (CMD_NOT_FOUND);
	}
	else if (mode == 2)
	{
		if (access(str, R_OK) == 0)
			return (0);
		return (FILE_NOT_READ);
	}
	if (access(str, W_OK) == 0)
		return (0);
	return (FILE_NOT_WRITE);
}

int	add_arguments(t_parser **split, t_cmd *new)
{
	int			i;
	int			k;
	t_parser	*pt;

	i = 0;
	k = -1;
	pt = *split;
	while (pt && ft_strncmp(pt->word, "|", 2))
	{
		pt = pt->next;
		i++;
	}
	new->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new->args)
		return (MALLOC);
	pt = (*split)->next;
	while (++k < i)
	{
//		printf("Split: %p\tPt: %p\n", *split, pt);
		printf("K: %d\tI: %d\tTmp:-->%p\n", k, i, (*split));
		new->args[k] = ft_strdup((*split)->word);
		if (!new->args[k])
			return (free_double_int(new->args, k));
		free((*split)->word);
		free(*split);
		*split = pt;
		if (*split)
			pt = (*split)->next;
	}
	new->args[k] = NULL;
	if (*split && !ft_strncmp((*split)->word, "|", 2))
		(*split) = (*split)->next;
	return (0);
}

t_cmd	*set_new_command(int *number)
{
	t_cmd		*new;
	t_here_doc	*hdoc;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	hdoc = (t_here_doc *)malloc(sizeof(t_here_doc));
	if (!new || !hdoc)
	{
		if (new)
			free(new);
		return (NULL);
	}
	new->n = *number;
	new->ok = 0;
	new->in_fd = 0;
	new->out_fd = 1;
	new->cmd = NULL;
	new->args = NULL;
	new->next = NULL;
	new->before = NULL;
	hdoc->first = 0;
	hdoc->if_hdoc = 0;
	hdoc->stop_word = NULL;
	new->here_doc = hdoc;
	(*number)++;
	return (new);
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
	{
		free(t1);
		return (MALLOC + 1);
	}
	free(t1);
	t1 = NULL;
	ret = check_access(t2, 1);
//	(ret && (free(t2)) && (t2 = NULL) && ((ret != CMD_NOT_FOUND) && ret++));
	if (ret)
	{
		free(t2);
		t2 = NULL;
		((ret != CMD_NOT_FOUND) && ret++);
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

int	add_command(t_min **tk, t_parser **split, t_cmd *new)
{
	int		err;
	char	*tmp;

	err = 0;
	printf("Cmd word:--%s--\n", (*split)->word);
	tmp = ft_strdup((*split)->word);
	if (!tmp)
		return (MALLOC);
	if (tmp[0] != '/')
		err = rel_path_cmd(tk, &tmp);
	new->cmd = tmp;
	return (err);
}
