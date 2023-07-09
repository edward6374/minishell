/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:47:54 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/08 18:24:33 by vduchi           ###   ########.fr       */
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

int	free_args(char **args, int idx)
{
	while (--idx)
		free(args[idx]);
	free(args);
	return (MALLOC);
}

int	add_arguments(t_parser **split, t_command *new)
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
			return (free_args(new->args, k));
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

t_command	*set_new_command(int *number)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->n = *number;
	new->ok = 0;
	new->in = 0;
	new->out = 1;
	new->if_here_doc = 0;
	new->cmd = NULL;
	new->args = NULL;
	new->here_doc = NULL;
	new->stop_word = NULL;
	new->next = NULL;
	new->before = NULL;
	(*number)++;
	return (new);
}

int	join_paths(char **tmp, char *env)
{
	int		ret;
	char	*t1;
	char	*t2;

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
	if (!ret)
	{
		free(*tmp);
		*tmp = t2;
		return (0);
	}
	free(t2);
	t2 = NULL;
	return (ret);
}

int	rel_path_cmd(t_minishell **tokens, char **tmp)
{
	int		i;
	int		ret;

	i = -1;
	while ((*tokens)->path[++i])
	{
		ret = join_paths(tmp, (*tokens)->path[i]);
		if (!ret)
			break ;
		else if (ret == CMD_NOT_FOUND)
			continue ;
		else
			return (ret - 1);
	}
	if (!(*tokens)->path[i])
		return (CMD_NOT_FOUND);
	return (0);
}

int	add_command(t_minishell **tokens, t_parser **split, t_command *new)
{
	int		err;
	char	*tmp;

	err = 0;
	printf("Cmd word:-->%s--<\n", (*split)->word);
	tmp = ft_strdup((*split)->word);
	if (!tmp)
		return (MALLOC);
	if (tmp[0] != '/')
		err = rel_path_cmd(tokens, &tmp);
	if (err)
		return (err);
	new->cmd = ft_strdup(tmp);
	if (!new->cmd)
	{
		free(tmp);
		return (MALLOC);
	}
	free(tmp);
	return (0);
}

