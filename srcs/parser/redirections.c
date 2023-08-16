/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:38:31 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 19:28:43 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"
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
	else
		(*tmp)->before = NULL;
}

int	minor_redir(t_parser **tmp, t_cmd *new, int mode)
{
	int	err;

	if (!mode)
	{
		if (new->hdoc->first)
			new->hdoc->first = 0;
		if (new->in_fd != 0)
			close(new->in_fd);
		err = check_access((*tmp)->next->word, 2);
		if (err)
			return (err);
		new->in_fd = open((*tmp)->next->word, O_RDWR);
	}
	else
	{
		new->hdoc->first = 1;
		new->hdoc->yes = 1;
		new->hdoc->stop = ft_strdup((*tmp)->next->word);
		if (!new->hdoc->stop)
			return (free_commands(&new, MALLOC));
	}
	change_tmp(tmp);
	return (0);
}

int	major_redir(t_parser **tmp, t_cmd *new, int mode)
{
	if (new->out_fd != 1)
		close(new->out_fd);
	if (check_access((*tmp)->next->word, 0))
		return (FILE_NOT_READ);
	if (mode)
		new->out_fd = open((*tmp)->next->word, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		new->out_fd = open((*tmp)->next->word, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (new->out_fd == -1)
		return (OPEN_FAILED);
	change_tmp(tmp);
	return (0);
}

int	rel_path_file(t_parser **tmp)
{
	char	*t1;
	char	*t2;
	char	*here;

	here = getcwd(NULL, 0);
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
		|| !ft_strncmp((*tmp)->word, ">>", 3)) && (*tmp)->next->word[0] != '/')
	{
		if (rel_path_file(tmp))
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
	return (0);
}
