/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:56:41 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/17 18:44:57 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

int	look_for_redir(t_parser **split, t_command *new)
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
			new->ok = err; // Da controllare se con altri errori c'e' da uscire direttamente o no
			return (err);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_command	*get_last_command(t_minishell **tokens)
{
	t_command	*tmp;

	if (!(*tokens)->command)
		return (NULL);
	tmp = (*tokens)->command;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	print_commands(t_minishell *tokens)
{
	int			i;
	int			k;
	t_command	*comm;

	i = 0;
	comm = tokens->command;
//	printf("Comm %p\n", comm);
	while (comm)
	{
		k = -1;
		printf("Tokens %d\t%p\n\tOk: %d\n\tIn: %d\n\tOut: %d\n\tCmd: %s\n", i, comm, comm->ok, comm->in, comm->out, comm->cmd);
		while (comm->args[++k])
			printf("\tArg %d:-->%s\n", k, comm->args[k]);
		printf("\tNext: %p\n\tBefore: %p\n", comm->next, comm->before);
		comm = comm->next;
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

int	create_token(t_minishell **tokens, t_parser **split, t_command *new)
{
	int			err;
	t_command	*lst;

	lst = get_last_command(tokens);
	err = add_command(tokens, split, new);
	if (err == MALLOC)
		return (MALLOC);
	else if (err)
		new->ok = err;
	if (add_arguments(split, new))
		return (MALLOC);
	if (!(*tokens)->command)
	{
		printf("First command\n");
		(*tokens)->command = new;
	}
	else
	{
		printf("Not first command\n");
		lst->next = new;
		lst->next->before = lst;
	}
	return (0);
}

int	load_commands(t_minishell *tokens, t_parser *split)
{
	int			err;
	t_command	*new;

	err = check_redir_syntax(split);
	if (err)
		return (err);
	while (split)
	{
		new = set_new_command(&tokens->num_cmds);
		if (!new)
			return (MALLOC);
		err = look_for_redir(&split, new);
		if (err == MALLOC)
			return (MALLOC);
		else if (err)		// Pulire il new
			return (0);
		err = create_token(&tokens, &split, new);
		if (err)
			return (err);
		new = NULL;
	}
	print_commands(tokens);
	return (0);
}
