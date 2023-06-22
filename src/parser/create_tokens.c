/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:56:41 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/22 19:34:10 by vduchi           ###   ########.fr       */
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

int	minor_redir(t_parser **tmp, t_parser **split, t_command *new)
{
	t_parser	*before_tmp;

	printf("In before: %d\tSplit %p\tTmp: %p\n", new->in, *split, *tmp);
	printf("Word: --%s--\n", (*tmp)->next->word);
	if (new->in != 0)
		close(new->in);
	new->in = open((*tmp)->next->word, O_RDWR);
	if (new->in == -1)
		return (OPEN_FAILED);
	before_tmp = (*tmp)->before;
//	printf("Before split: %p\tTmp: %p\n", before_tmp, *tmp);
	free_lst_redir(tmp);
//	printf("After free split: %p\n", *tmp);
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
	*tmp = *split;
	printf("In after: %d\tSplit %p\n", new->in, *split);
	return (0);
}

int	major_redir(t_parser **tmp, t_parser **split, t_command *new)
{
	t_parser	*before_tmp;

	printf("Out before: %d\n", new->out);
	if (new->out != 1)
		close(new->out);
	new->out = open((*tmp)->next->word, O_RDWR | O_CREAT, 0644);
	if (new->out == -1)
		return (OPEN_FAILED);
	before_tmp = (*tmp)->before;
	free_lst_redir(tmp);
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
	*tmp = *split;
	printf("Out after: %d\n", new->out);
	return (0);
}

int	double_minor_redir(t_parser **tmp, t_parser **split, t_command *new)
{
	(void)tmp;
	(void)split;
	(void)new;
	return (0);
}

int	double_major_redir(t_parser **tmp, t_parser **split, t_command *new)
{
	(void)tmp;
	(void)split;
	(void)new;
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

int	take_redir(t_parser **tmp, t_parser **split, t_command *new)
{
	int	err;

	err = 0;
	if ((!ft_strncmp((*tmp)->word, "<", 2) || !ft_strncmp((*tmp)->word, ">", 2)
		|| !ft_strncmp((*tmp)->word, "<<", 3)
		|| !ft_strncmp((*tmp)->word, ">>", 3)) && (*tmp)->next->word[0] != '/')
		err = rel_path_file(tmp);
	if (err)
		return (err);
	if (!ft_strncmp((*tmp)->word, "<", 2))
		return (minor_redir(tmp, split, new));
	else if (!ft_strncmp((*tmp)->word, ">", 2))
		return (major_redir(tmp, split, new));
	else if (!ft_strncmp((*tmp)->word, "<<", 3))
		return (double_minor_redir(tmp, split, new));
	else if (!ft_strncmp((*tmp)->word, ">>", 3))
		return (double_major_redir(tmp, split, new));
	printf("No redir\tWord: --%s--\n", (*tmp)->word);
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

int	check_access(char **t1, char *str, int mode)
{
	free(*t1);
	*t1 = NULL;
	if (mode == 1)
	{
		if (access(str, X_OK) == 0)
			return (0);
		if (access(str, F_OK) == 0)
			return (CMD_FOUND_NOT_EX);
		return (CMD_NOT_FOUND);
	}
	else if (mode == 2)
	{
		if (access(str, R_OK) == 0)
			return (0);
		return (FILE_NOT_READ);
	}
	if (access(str, W_OK) == 0)
		return (0);
	return (FILE_NOT_WRITE);
}

int	join_paths(char **tmp, char *env)
{
	int		ret;
	char	*t1;
	char	*t2;

	t1 = ft_strjoin(env, "/");
	if (!t1)
		return (MALLOC + 1);
	t2 = ft_strjoin(t1, *tmp);
	if (!t2)
	{
		free(t1);
		return (MALLOC + 1);
	}
	ret = check_access(&t1, t2, 1);
	if (!ret)
	{
		free(*tmp);
		*tmp = t2;
		return (0);
	}
	else
	{
		free(t2);
		return (ret);
	}
}

int	rel_path_cmd(t_minishell **tokens, char **tmp)
{
	int		i;
	int		ret;

	i = -1;
	while ((*tokens)->path[++i])
	{
		ret = join_paths(tmp, (*tokens)->path[i]);
		if (!ret)
			break ;
		else if (ret == CMD_NOT_FOUND)
			continue ;
		else
			return (ret - 1);
	}
	if (!(*tokens)->path[i])
		return (CMD_NOT_FOUND);
	return (0);
}

int	add_command(t_minishell **tokens, t_parser **split, t_command *new)
{
	int		err;
	char	*tmp;

	err = 0;
	printf("Cmd word:-->%s--<\n", (*split)->word);
	tmp = ft_strdup((*split)->word);
	if (!tmp)
		return (MALLOC);
	if (tmp[0] != '/')
		err = rel_path_cmd(tokens, &tmp);
	if (err)
		return (err);
	new->cmd = ft_strdup(tmp);
	if (!new->cmd)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
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
//		printf("Split: %p\tPt: %p\n", *split, pt);
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
		err = take_redir(&tmp, split, new);
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
	if (add_command(tokens, split, new) || add_arguments(split, new))
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
		printf("First command\n");
		(*tokens)->command = new;
	}
	else
	{
		printf("Not first command\n");
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
