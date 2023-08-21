/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:56:41 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/21 10:29:06 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

static int	look_for_redir(t_parser **list, t_cmd *new)
{
	int			err;
	t_parser	*tmp;

	tmp = (*list);
	while (tmp && ft_strncmp(tmp->word, "|", 2))
	{
		err = take_redir(&tmp, new);
		if (err == MALLOC)
			return (free_parser(*list, MALLOC));
		else if (err)
		{
			printf("Take redir error: %d\n", err);
			new->ok = err;
			return (err);
		}
		tmp = tmp->next;
	}
	return (0);
}

// void	print_commands(t_min *tk)
// {
// 	int		i;
// 	int		k;
// 	t_cmd	*cmd;

// 	i = 0;
// 	cmd = tk->cmds;
// 	printf("Comm %p\n", cmd);
// 	while (cmd)
// 	{
// 		k = -1;
// 		printf("Tokens %d\t%p\n\tOk: %d\n\tIn: %d\n\tOut: %d\n\tCmd: %s\n", i,
// 				cmd, cmd->ok, cmd->in_fd, cmd->out_fd, cmd->cmd);
// 		while (cmd->args[++k])
// 			printf("\tArg %d:-->%s--\n", k, cmd->args[k]);
// 		printf("\tNext: %p\n\tBefore: %p\n", cmd->next, cmd->before);
// 		cmd = cmd->next;
// 		i++;
// 	}
// }

static int	check_redir_syntax(t_parser *list)
{
	while (list)
	{
		if (!ft_strncmp(list->word, "|", 2) && (list->before == NULL
				|| !ft_strncmp(list->before->word, "<", 2)
				|| !ft_strncmp(list->before->word, "<<", 3)
				|| !ft_strncmp(list->before->word, ">", 2)
				|| !ft_strncmp(list->before->word, ">>", 3)))
			return (PIPE_FIRST);
		else if ((!ft_strncmp(list->word, "<", 2) || !ft_strncmp(list->word,
					"<<", 3) || !ft_strncmp(list->word, ">", 2)
				|| !ft_strncmp(list->word, ">>", 3)) && list->next == NULL)
			return (ONLY_REDIR);
		list = list->next;
	}
	return (0);
}

static int	create_token(t_min **tk, t_parser **list, t_cmd *new)
{
	int		err;
	t_cmd	*lst;

	lst = get_last_cmd(tk);
	err = add_command(tk, list, new);
	if (err == MALLOC)
		return (free_commands(&new, free_parser(*list, MALLOC)));
	else if (err && !new->ok)
		new->ok = err;
	if (add_arguments(list, new))
		return (free_commands(&new, free_parser(*list, MALLOC)));
	if (!(*tk)->cmds)
		(*tk)->cmds = new;
	else
	{
		lst->next = new;
		lst->next->before = lst;
	}
	return (0);
}

int	load_commands(t_min *tk, t_parser *list)
{
	int		err;
	t_cmd	*new;

	err = check_redir_syntax(list);
	if (err)
		return (free_parser(list, free_all(tk, err)));
	while (list)
	{
		new = set_new_command(&tk->num_cmds);
		if (!new)
			return (free_parser(list, free_all(tk, MALLOC)));
		err = look_for_redir(&list, new);
		if (err == MALLOC)
			return (free_all(tk, MALLOC));
		err = create_token(&tk, &list, new);
		if (err)
			return (free_all(tk, err));
		new = NULL;
	}
//	print_commands(tk);
	return (0);
}
