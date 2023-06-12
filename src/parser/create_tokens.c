/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:56:41 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/12 21:16:18 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	minor_redir(t_minishell **tokens, t_parser **tmp, t_command **lst, t_command *new)
{
	new->in = open((*tmp)->next->word, O_RDWR);
	if (new->in == -1)
		return (OPEN_FAILED);
	return (1);
}

int	check_redir_syntax(t_parser *tmp)
{
	while (tmp)
	{
		if (!ft_strncmp(tmp->word, "|", 2) && (tmp->before == NULL
			|| !ft_strncmp(tmp->before->word, "<", 2)
			|| !ft_strncmp(tmp->before->word, "<<", 3)
			|| !ft_strncmp(tmp->before->word, ">", 2)
			|| !ft_strncmp(tmp->before->word, ">>", 3)))
			return (PIPE_FIRST); //	Significa che c'e' una redirezione prima di un pipe o il pipe e' al primo posto
		else if ((!ft_strncmp(tmp->word, "<", 2)
			|| !ft_strncmp(tmp->word, "<<", 3)
			|| !ft_strncmp(tmp->word, ">", 2)
			|| !ft_strncmp(tmp->word, ">>", 3)) && tmp->next == NULL)
			return (ONLY_REDIR); // Significa che c'e' una redirezione, ma dopo non c'e' scritto niente
		tmp = tmp->next;
	}
	return (0);
}

int	take_redir(t_minishell **tokens, t_parser **tmp, t_command **lst, t_command *new)
{
	if (!ft_strncmp(tmp->word, "<", 2))
		return (minor_redir(tokens, lst, tmp, new));
	else if (!ft_strncmp(tmp->word, ">", 2))
		return (major_redir(tokens, lst, tmp, new));
	else if (!ft_strncmp(tmp->word, "<<", 3))
		return (double_minor_redir(tokens, lst, tmp, new));
	else if (!ft_strncmp(tmp->word, ">>", 3))
		return (double_major_redir(tokens, lst, tmp, new));
	return (0);
}

int	create_command(t_minishell **tokens, t_parser **tmp, t_command **lst)
{
	int			ret;
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (MALLOC);
	ret = take_redir(tokens, lst, tmp, new);
	if (ret > 1)
		return (ret - 1);
	else (ret)
		return (0);
	if ((tmp->before == NULL || !ft_strncmp(tmp->before->word, "|", 2))
			&& (!lst || (lst && !lst->cmd)))
		err = add_command(tokens, lst, tmp, new);
	err = add_arguments(tokens, lst, tmp, new);
	if (err)
		return (err);
	return (0);
}

int	load_commands(t_minishell *tokens, t_parser *split)
{
	int			err;
	t_parser	*tmp;
	t_command	*lst;

	tmp = split;
	lst = tokens->command;
	err = check_redir_syntax(tmp);
	if (err)
		return (err);
	while (tmp)
	{
		err = create_command(&tokens, &tmp, &lst);
		if (err)
			return (err);
	}
	return (0);
}
