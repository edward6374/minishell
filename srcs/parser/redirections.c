/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:38:31 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/12 18:29:08 by vduchi           ###   ########.fr       */
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
	if (!mode)
	{
		printf("In before: %d\tTmp: %p\n", new->in_fd, *tmp);
		printf("Word: --%s--\n", (*tmp)->next->word);
		if (new->here_doc->first)
			new->here_doc->first = 0;
		if (new->in_fd != 0)
			close(new->in_fd);
		new->in_fd = open((*tmp)->next->word, O_RDWR);
		if (new->in_fd == -1)
			return (OPEN_FAILED);
		printf("In after: %d\tTmp: %p\n", new->in_fd, *tmp);
	}
	else
	{
		printf("Old tmp before: %p\n", (*tmp)->before->word);
		printf("Double minor stop word: %s\n", (*tmp)->next->word);
		new->here_doc->first = 1;
		new->here_doc->if_hdoc = 1;
		new->here_doc->stop_word = ft_strdup((*tmp)->next->word);
		if (!new->here_doc->stop_word)
		{
			free_commands(&new);
			return (MALLOC);
		}
		printf("New tmp before: %p\n", (*tmp)->before->word);
	}
	change_tmp(tmp);
	return (0);
}

int	major_redir(t_parser **tmp, t_cmd *new, int mode)
{
	printf("Out before: %d\n", new->out_fd);
	if (new->out_fd != 1)
		close(new->out_fd);
	if (mode)
		new->out_fd = open((*tmp)->next->word, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		new->out_fd = open((*tmp)->next->word, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (new->out_fd == -1)
		return (OPEN_FAILED);
	change_tmp(tmp);
	printf("Out after: %d\n", new->out_fd);
	return (0);
}

int	rel_path_file(t_parser **tmp)
{
	char	*t1;
	char	*t2;
	char	here[256];

	if (getcwd(here, sizeof(here)) == NULL)
		return (GETCWD_ERROR);
	t1 = ft_strjoin(here, "/");
	if (!t1)
		return (MALLOC);
	t2 = ft_strjoin(t1, (*tmp)->next->word);
	if (!t2)
	{
		free(t1);
		return (MALLOC);
	}
	free(t1);
	free((*tmp)->next->word);
	(*tmp)->next->word = t2;
	t2 = NULL;
	return (0);
}

int	take_redir(t_parser **tmp, t_cmd *new)
{
	int	err;

	err = 0;
	if ((!ft_strncmp((*tmp)->word, "<", 2) || !ft_strncmp((*tmp)->word, ">", 2)
		|| !ft_strncmp((*tmp)->word, ">>", 3)) && (*tmp)->next->word[0] != '/')
		err = rel_path_file(tmp);
	if (err)
	{
		free_commands(&new);
		return (err);
	}
	if (!ft_strncmp((*tmp)->word, "<", 2))
		return (minor_redir(tmp, new, 0));
	else if (!ft_strncmp((*tmp)->word, "<<", 3))
		return (minor_redir(tmp, new, 1));
	else if (!ft_strncmp((*tmp)->word, ">", 2))
		return (major_redir(tmp, new, 0));
	else if (!ft_strncmp((*tmp)->word, ">>", 3))
		return (major_redir(tmp, new, 1));
	printf("No redir\tWord: --%s--\tError value: %d\n", (*tmp)->word, err);
	return (0);
}
