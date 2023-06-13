/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:56:41 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/13 20:24:10 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	minor_redir(t_minishell **tokens, t_parser **tmp, t_command *new)
{
	(void)tokens;
	printf("In before: %d\n", new->in);
	new->in = open((*tmp)->next->word, O_RDWR);
	if (new->in == -1)
		return (OPEN_FAILED);
	(*tmp) = (*tmp)->next->next;
	printf("Minor %d\n", new->in);
	return (1);
}

int	major_redir(t_minishell **tokens, t_parser **tmp, t_command *new)
{
	(void)tokens;
	new->out = open((*tmp)->next->word, O_RDWR);
	if (new->out == -1)
		return (OPEN_FAILED);
	(*tmp) = (*tmp)->next->next;
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

int	double_minor_redir(t_minishell **tokens, t_parser **tmp, t_command *new)
{
	(void)tokens;
	(void)tmp;
	(void)new;
	return (1);
}

int	double_major_redir(t_minishell **tokens, t_parser **tmp, t_command *new)
{
	(void)tokens;
	(void)tmp;
	(void)new;
	return (1);
}

int	take_redir(t_minishell **tokens, t_parser **tmp, t_command *new)
{
	if (!ft_strncmp((*tmp)->word, "<", 2))
		return (minor_redir(tokens, tmp, new));
	else if (!ft_strncmp((*tmp)->word, ">", 2))
		return (major_redir(tokens, tmp, new));
	else if (!ft_strncmp((*tmp)->word, "<<", 3))
		return (double_minor_redir(tokens, tmp, new));
	else if (!ft_strncmp((*tmp)->word, ">>", 3))
		return (double_major_redir(tokens, tmp, new));
	printf("No redir\n");
	return (0);
}

t_command	*set_new_command(void)
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
	return (new);
}

int	add_command(t_minishell **tokens, t_parser **tmp, t_command *new)
{
	(void)tokens;
	printf("Tmp word:-->%s--<\n", (*tmp)->word);
	new->cmd = ft_strdup((*tmp)->word);
	if (!new->cmd)
		return (1);
	(*tmp) = (*tmp)->next;
	return (0);
}

int	free_args(char **args, int idx)
{
	while (--idx)
		free(args[idx]);
	free(args);
	return (1);
}

int	add_arguments(t_minishell **tokens, t_parser **tmp, t_command *new)
{
	int			i;
	int			k;
	t_parser	*pt;

	(void)tokens;
	i = 0;
	k = -1;
	pt = (*tmp);
	while (pt && ft_strncmp(pt->word, "|", 2))
	{
		pt = pt->next;
		i++;
	}
	new->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new->args)
		return (1);
	while (++k < i)
	{
//		printf("K: %d\tI: %d\tTmp:-->%p\n", k, i, (*tmp));
		new->args[k] = ft_strdup((*tmp)->word);
		if (!new->args[k])
			return (free_args(new->args, k));
		(*tmp) = (*tmp)->next;
	}
	new->args[k] = NULL;
	if ((*tmp) && !ft_strncmp((*tmp)->word, "|", 2))
		(*tmp) = (*tmp)->next;
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

int	create_command(t_minishell **tokens, t_parser **tmp)
{
	int			ret;
	t_command	*new;
	t_command	*lst;

	new = set_new_command();
	if (!new)
		return (MALLOC);
	lst = get_last_command(tokens);
	printf("New: %p\nDouble: %p\n", new, &new);
	ret = take_redir(tokens, tmp, new);
	if (ret > 1)
		return (ret - 1);
//	if ((tmp->before == NULL || !ft_strncmp(tmp->before->word, "|", 2))
//			&& (!lst || (lst && !lst->cmd)))
	ret = add_command(tokens, tmp, new);
	if (ret)
		return (ret);
	if (!(*tmp))
		return (0);
	ret = add_arguments(tokens, tmp, new);
	if (ret)
	{
		return (ret);
	}
	if (!(*tokens)->command)
	{
//		printf("Empty\n");
		(*tokens)->command = new;
	}
	else
	{
//		printf("Looped\n");
		lst->next = new;
		lst->next->before = lst;
	}
	new = NULL;
	return (0);
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

int	load_commands(t_minishell *tokens, t_parser *split)
{
	int			err;
	t_parser	*tmp;
//	t_command	*lst;

	tmp = split;
//	lst = tokens->command;
	err = check_redir_syntax(tmp);
	if (err)
		return (err);
//	printf("Lst load: %p\tTokens->command: %p\n", &lst, &tokens->command);
	while (tmp)
	{
		err = create_command(&tokens, &tmp);
		if (err)
			return (err);
	}
	print_commands(tokens);
	return (0);
}
