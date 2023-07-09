/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 18:38:31 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/08 18:39:12 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

void	change_tmp(t_parser **tmp)
{
	t_parser	*next_tmp;
	t_parser	*before_tmp;

	before_tmp = (*tmp)->before;
//	free_lst_redir(tmp);
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

int	minor_redir(t_parser **tmp, t_command *new, int mode)
{
	if (!mode)
	{
		printf("In before: %d\tTmp: %p\n", new->in, *tmp);
		printf("Word: --%s--\n", (*tmp)->next->word);
		if (new->in != 0)
			close(new->in);
		new->in = open((*tmp)->next->word, O_RDWR);
		if (new->in == -1)
			return (OPEN_FAILED);
		printf("In after: %d\tTmp: %p\n", new->in, *tmp);
	}
	else
	{
		printf("Old tmp before: %p\n", (*tmp)->before->word);
		printf("Double minor stop word: %s\n", (*tmp)->next->word);
		new->if_here_doc = 1;
		new->stop_word = ft_strdup((*tmp)->next->word);
		if (!new->stop_word)
			return (MALLOC);
		printf("New tmp before: %p\n", (*tmp)->before->word);
	}
	change_tmp(tmp);
	return (0);
}

int	major_redir(t_parser **tmp, t_command *new, int mode)
{
	printf("Out before: %d\n", new->out);
	if (new->out != 1)
		close(new->out);
	if (mode)
		new->out = open((*tmp)->next->word, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		new->out = open((*tmp)->next->word, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (new->out == -1)
		return (OPEN_FAILED);
	change_tmp(tmp);
	printf("Out after: %d\n", new->out);
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

int	take_redir(t_parser **tmp, t_command *new)
{
	int	err;

	err = 0;
	if ((!ft_strncmp((*tmp)->word, "<", 2) || !ft_strncmp((*tmp)->word, ">", 2)
		|| !ft_strncmp((*tmp)->word, ">>", 3)) && (*tmp)->next->word[0] != '/')
		err = rel_path_file(tmp);
	if (err)
		return (err);
	if (!ft_strncmp((*tmp)->word, "<", 2))
		return (minor_redir(tmp, new, 0));
	else if (!ft_strncmp((*tmp)->word, "<<", 3))
		return (minor_redir(tmp, new, 1));
	else if (!ft_strncmp((*tmp)->word, ">", 2))
		return (major_redir(tmp, new, 0));
	else if (!ft_strncmp((*tmp)->word, ">>", 3))
		return (major_redir(tmp, new, 1));
	printf("No redir\tWord: --%s--\n", (*tmp)->word);
	return (0);
}
