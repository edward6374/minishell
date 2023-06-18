/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:56:41 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/18 15:21:23 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

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

void	free_lst_redir(t_parser **split)
{
	t_parser	*next_tmp;

	next_tmp = (*split)->next;
	free((*split)->word);
	free(*split);
	*split = next_tmp;
	next_tmp = (*split)->next;
	free((*split)->word);
	free(*split);
	*split = next_tmp;
}

int	minor_redir(t_parser **split, t_command *new)
{
	t_parser	*tmp;

	printf("In before: %d\n", new->in);
	new->in = open((*split)->next->word, O_RDWR);
	if (new->in == -1)
		return (OPEN_FAILED);
	tmp = (*split)->before;
	free_lst_redir(split);
	if (tmp)
	{
		tmp->next = *split;
		(*split)->before = tmp;
		*split = tmp;
		tmp = NULL;
	}
	else
		(*split)->before = NULL;
	printf("Minor %d\n", new->in);
	return (0);
}

int	major_redir(t_parser **split, t_command *new)
{
	t_parser	*tmp;

	printf("Out before: %d\n", new->out);
	new->out = open((*split)->next->word, O_RDWR);
	if (new->out == -1)
		return (OPEN_FAILED);
	tmp = (*split)->before;
	free_lst_redir(split);
	if (tmp)
	{
		tmp->next = *split;
		(*split)->before = tmp;
		*split = tmp;
		tmp = NULL;
	}
	else
		(*split)->before = NULL;
	printf("Minor %d\n", new->out);
	return (0);
}

int	double_minor_redir(t_parser **split, t_command *new)
{
	(void)split;
	(void)new;
	return (0);
}

int	double_major_redir(t_parser **split, t_command *new)
{
	(void)split;
	(void)new;
	return (0);
}

int	take_redir(t_parser **split, t_command *new)
{
	if (!ft_strncmp((*split)->word, "<", 2))
		return (minor_redir(split, new));
	else if (!ft_strncmp((*split)->word, ">", 2))
		return (major_redir(split, new));
	else if (!ft_strncmp((*split)->word, "<<", 3))
		return (double_minor_redir(split, new));
	else if (!ft_strncmp((*split)->word, ">>", 3))
		return (double_major_redir(split, new));
	printf("No redir\n");
	return (0);
}

t_command	*set_new_command(t_minishell **tokens)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->ok = 1;
	new->in = 0;
	new->out = 1;
	new->cmd = NULL;
	new->args = NULL;
	new->next = NULL;
	new->before = NULL;
	(*tokens)->num_comms++;
	return (new);
}

int	add_command(t_parser **split, t_command *new)
{
	printf("Cmd word:-->%s--<\n", (*split)->word);
	new->cmd = ft_strdup((*split)->word);
	if (!new->cmd)
		return (1);
	return (0);
}

int	free_args(char **args, int idx)
{
	while (--idx)
		free(args[idx]);
	free(args);
	return (1);
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
		return (1);
	pt = (*split)->next;
	while (++k < i)
	{
		printf("Split: %p\tPt: %p\n", *split, pt);
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

int	look_for_redir(t_parser **split, t_command *new)
{
	int			err;
	t_parser	*tmp;

	tmp = (*split);
	while (tmp && ft_strncmp(tmp->word, "|", 2))
	{
		err = take_redir(split, new);
		if (err)
			return (err);
		tmp = tmp->next;
	}
	return (0);
}

int	create_command(t_minishell **tokens, t_parser **split)
{
	int			err;
	t_command	*new;
	t_command	*lst;

	new = set_new_command(tokens);
	if (!new)
		return (MALLOC);
	err = look_for_redir(split, new);
	if (err)
		return (err);
	lst = get_last_command(tokens);
//	printf("New: %p\nDouble: %p\n", new, &new);
	if (add_command(split, new) || add_arguments(split, new))
		return (MALLOC);
//	if (add_arguments(tokens, split, new))
//		return (MALLOC);
//	if ((split->before == NULL || !ft_strncmp(split->before->word, "|", 2))
//			&& (!lst || (lst && !lst->cmd)))
//	if (add_command(tokens, split, new))
//		return (MALLOC);
//	if (!(*split))
//		return (0);
//	ret = add_arguments(tokens, split, new);
//	if (ret)
//	{
//		return (ret);
//	}
	if (!(*tokens)->command)
	{
		printf("Empty\n");
		(*tokens)->command = new;
	}
	else
	{
		printf("Looped\n");
		lst->next = new;
		lst->next->before = lst;
	}
	new = NULL;
	return (0);
}

int	load_commands(t_minishell *tokens, t_parser *split)
{
	int			err;
//	t_command	*lst;

//	lst = tokens->command;
	err = check_redir_syntax(split);
	if (err)
		return (err);
//	printf("Lst load: %p\tTokens->command: %p\n", &lst, &tokens->command);
	while (split)
	{
		err = create_command(&tokens, &split);
		if (err)
			return (err);
	}
	print_commands(tokens);
	return (0);
}
