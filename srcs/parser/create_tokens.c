/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:56:41 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/09 17:05:33 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

int	look_for_redir(t_parser **split, t_cmd *new)
{
	int			err;
	t_parser	*tmp;

	tmp = (*split);
	while (tmp && ft_strncmp(tmp->word, "|", 2))
	{
		err = take_redir(&tmp, new);
		if (err == MALLOC)
			return (MALLOC);
		else if (err)
		{
			printf("Take redir error: %d\n", err);
			new->ok = err; // Da controllare se con altri errori c'e' da uscire direttamente o no
			return (err);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_cmd	*get_last_cmd(t_min **tk)
{
	t_cmd	*tmp;

	if (!(*tk)->cmds)
		return (NULL);
	tmp = (*tk)->cmds;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	print_commands(t_min *tk)
{
	int			i;
	int			k;
	t_cmd		*cmd;

	i = 0;
	cmd = tk->cmds;
	printf("Comm %p\n", cmd);
	while (cmd)
	{
		k = -1;
		printf("Tokens %d\t%p\n\tOk: %d\n\tIn: %d\n\tOut: %d\n\tCmd: %s\n", i, cmd, cmd->ok, cmd->in_fd, cmd->out_fd, cmd->cmd);
		while (cmd->args[++k])
			printf("\tArg %d:-->%s\n", k, cmd->args[k]);
		printf("\tNext: %p\n\tBefore: %p\n", cmd->next, cmd->before);
		cmd = cmd->next;
		i++;
	}
}

int	check_redir_syntax(t_parser *split)
{
	while (split)
	{
		if (!ft_strncmp(split->word, "|", 2) && (split->before == NULL
			|| !ft_strncmp(split->before->word, "<", 2)
			|| !ft_strncmp(split->before->word, "<<", 3)
			|| !ft_strncmp(split->before->word, ">", 2)
			|| !ft_strncmp(split->before->word, ">>", 3)))
			return (PIPE_FIRST); //	Significa che c'e' una redirezione prima di un pipe o il pipe e' al primo posto
		else if ((!ft_strncmp(split->word, "<", 2)
			|| !ft_strncmp(split->word, "<<", 3)
			|| !ft_strncmp(split->word, ">", 2)
			|| !ft_strncmp(split->word, ">>", 3)) && split->next == NULL)
			return (ONLY_REDIR); // Significa che c'e' una redirezione, ma dopo non c'e' scritto niente
		split = split->next;
	}
	return (0);
}

int	create_token(t_min **tk, t_parser **split, t_cmd *new)
{
	int			err;
	t_cmd	*lst;

	lst = get_last_cmd(tk);
	printf("Create token word: %s\n", (*split)->word);
	err = add_command(tk, split, new);
	if (err == MALLOC)
		return (MALLOC);
	else if (err && !new->ok)
		new->ok = err;
	if (add_arguments(split, new))
		return (MALLOC);
	if (!(*tk)->cmds)
	{
		printf("First command\n");
		(*tk)->cmds = new;
	}
	else
	{
		printf("Not first command\n");
		lst->next = new;
		lst->next->before = lst;
	}
	return (0);
}

int	load_commands(t_min *tk, t_parser *split)
{
	int			err;
	t_cmd	*new;

	err = check_redir_syntax(split);
	if (err)
		return (err);
	while (split)
	{
		printf("Load_commands: --%s--\n", split->word);
		new = set_new_command(&tk->num_cmds);
		if (!new)
			return (MALLOC);
		err = look_for_redir(&split, new);
		if (err == MALLOC)
		{
			printf("Malloc error\n");
			return (MALLOC);
		}
		else if (err)		// Pulire il new
		{
			printf("Here\n");
			new->ok = err;
		}
		err = create_token(&tk, &split, new);
		if (err)
			return (err);
		printf("Token created\n");
		new = NULL;
	}
	print_commands(tk);
	return (0);
}
