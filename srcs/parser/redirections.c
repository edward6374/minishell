/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:38:31 by vduchi            #+#    #+#             */
/*   Updated: 2023/09/02 11:56:46 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>

void	change_tmp(t_parser **tmp)
{
	t_parser	*next_tmp;
	t_parser	*before_tmp;

	before_tmp = (*tmp)->before;
	next_tmp = (*tmp)->next;
	free((*tmp)->word);
	free(*tmp);
	*tmp = next_tmp;
	next_tmp = (*tmp)->next;
	free((*tmp)->word);
	free(*tmp);
	*tmp = next_tmp;
	if (before_tmp)
	{
		before_tmp->next = *tmp;
		if (*tmp)
			(*tmp)->before = before_tmp;
		*tmp = before_tmp;
		before_tmp = NULL;
	}
	else if (*tmp)
		(*tmp)->before = NULL;
}

int	minor_redir(t_parser **tmp, t_cmd *new, int mode)
{
	int	err;

	err = 0;
	if (!mode)
	{
		if (new->hdoc->first)
			new->hdoc->first = 0;
		if (new->in_fd != 0)
			close(new->in_fd);
		err = check_access(NULL, (*tmp)->next->word, 2);
		if (!err)
			new->in_fd = open((*tmp)->next->word, O_RDWR);
	}
	else
	{
		new->hdoc->yes = 1;
		new->hdoc->first = 1;
		new->hdoc->stop = ft_strdup((*tmp)->next->word);
		if (!new->hdoc->stop)
			return (free_commands(&new, MALLOC));
	}
	if (!err && new->err_f)
		free_err_f(&new->err_f);
	change_tmp(tmp);
	return (err);
}

int	major_redir(t_parser **tmp, t_cmd *new, int mode)
{
	int	err;

	err = 0;
	if (new->out_fd != 1 && mode)
		close(new->out_fd);
	err = check_access(NULL, (*tmp)->next->word, 0);
	if (!err)
	{
		if (mode)
			new->out_fd = open((*tmp)->next->word, O_RDWR | O_APPEND | O_CREAT,
				0644);
		else
			new->out_fd = open((*tmp)->next->word, O_RDWR | O_TRUNC | O_CREAT,
				0644);
		if (new->err_f)
			free_err_f(&new->err_f);
	}
	change_tmp(tmp);
	return (err);
}

int	rel_path_file(t_parser **tmp, t_cmd *new)
{
	char	*t1;
	char	*t2;
	char	*here;

	here = getcwd(NULL, 0);
	new->err_f = ft_strdup((*tmp)->next->word);
	t1 = ft_strjoin(here, "/");
	if (!t1)
		return (MALLOC);
	free(here);
	t2 = ft_strjoin(t1, (*tmp)->next->word);
	if (!t2)
		return (free_pointer(t1, MALLOC));
	free(t1);
	free((*tmp)->next->word);
	(*tmp)->next->word = t2;
	t2 = NULL;
	return (0);
}

int	take_redir(t_parser **tmp, t_cmd *new)
{
	if ((!ft_strncmp((*tmp)->word, "<", 2) || !ft_strncmp((*tmp)->word, ">", 2)
			|| !ft_strncmp((*tmp)->word, ">>", 3))
		&& (*tmp)->next->word[0] != '/')
	{
		if (rel_path_file(tmp, new))
			return (free_commands(&new, MALLOC));
	}
	if (!ft_strncmp((*tmp)->word, "<", 2))
		return (minor_redir(tmp, new, 0));
	else if (!ft_strncmp((*tmp)->word, "<<", 3))
		return (minor_redir(tmp, new, 1));
	else if (!ft_strncmp((*tmp)->word, ">", 2))
		return (major_redir(tmp, new, 0));
	else if (!ft_strncmp((*tmp)->word, ">>", 3))
		return (major_redir(tmp, new, 1));
	return (-1);
}
