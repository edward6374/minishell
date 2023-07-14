/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/14 14:23:24 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

void	set_vars(t_vars *vars, char *s)
{
	vars->i = -1;
	vars->count = -1;
	vars->sin_qts = 0;
	vars->dbl_qts = 0;
	vars->out_qts = 1;
	vars->num_qts = 0;
	vars->start_point = 0;
	vars->s = s;
}
/*
void	set_int_arr(int *arr)
{
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 1;
	arr[3] = 0;
	arr[4] = 0;
}
*/
int	add_word(t_parser **temp, char *word)
{
	t_parser	*new;

//	printf("Add word: %s\n", word);
	printf("Add word: --%s--\n", word);
	if (!(*temp)->word)
		(*temp)->word = word;
	else
	{
		new = (t_parser *)malloc(sizeof(t_parser));
		if (!new)
		{
			free(word);
			return (MALLOC);
		}
		new->word = word;
		new->next = NULL;
		new->before = (*temp);
		//		printf("Here Tmp: %p\n", *temp);
		(*temp)->next = new;
		(*temp) = (*temp)->next;
		//		printf("Then Tmp: %p\n", *temp);
		new = NULL;
	}
	return (0);
}

int	add_redir(t_parser **temp, t_vars *vars, int *idx, int redir)
{
	char	*word;

	if (redir > 0 && (vars->s[*idx] == '<' || vars->s[*idx] == '>'))
	{
		if ((vars->s[*idx] == '<' && vars->s[*idx + 1] == '<')
		|| (vars->s[*idx] == '>' && vars->s[*idx + 1] == '>'))
		{
			redir++;
			(*idx)++;
		}
		word = ft_substr(vars->s, vars->start_point, redir);
		if (!word || add_word(temp, word))
			return (MALLOC);
	}
	vars->start_point = *idx + 1;
	return (0);
}

int	create_word(t_parser **temp, t_vars *vars, int *idx)
{
	int		len;
	int		redir;
	char	*word;

	redir = 0;
//	printf("Create word: Idx: %d\tStart: %d\tCar Idx: --%c--\n", *idx, vars->start_point, vars->s[*idx]);
	if (*idx == vars->start_point)
		len = 1;
	else
	{
		redir++;
		len = *idx - vars->start_point;
	}
	if (len == 1 && ((vars->s[*idx] == '<' && vars->s[*idx + 1] == '<')
		|| (vars->s[*idx] == '>' && vars->s[*idx + 1] == '>')))
	{
		len++;
		(*idx)++;
	}
	else if (len != 1 && vars->s[*idx + 1] == '\0' && vars->s[*idx] != ' ')
		len++;
	word = ft_substr(vars->s, vars->start_point, len);
	if (!word || add_word(temp, word))
		return (MALLOC);
	vars->start_point = vars->start_point + len;
	return (add_redir(temp, vars, idx, redir));
	/*
	if (*idx == vars->start_point)
	{
		printf("If\n");
		len = 1;
		if ((vars->s[*idx] == '<' && vars->s[*idx + 1] == '<')
		|| (vars->s[*idx] == '>' && vars->s[*idx + 1] == '>'))
		{
			len++;
			(*idx)++;
		}
		word = ft_substr(vars->s, start, len);
		if (!word || add_word(temp, word))
			return (MALLOC);
	}
	else
	{
		printf("Else\n");
		len = *idx - vars->start_point;
		if (vars->s[*idx + 1] == '\0' && vars->s[*idx] != ' ')
			len++;	
		word = ft_substr(vars->s, start, len);
		if (!word || add_word(temp, word))
			return (MALLOC);
		if (vars->s[*idx] == '<' || vars->s[*idx] == '>')
		{
			redir = 1;
			if ((vars->s[*idx] == '<' && vars->s[*idx + 1] == '<')
			|| (vars->s[*idx] == '>' && vars->s[*idx + 1] == '>'))
			{
				redir++;
				(*idx)++;
			}
			word = ft_substr(vars->s, start + len, redir);
			if (!word || add_word(temp, word))
				return (MALLOC);
		}
	}
	*/
}

int	find_more_words(t_parser **temp, t_vars *vars)
{
	int	idx;

	idx = vars->start_point - 1;
//	printf("Before: Arr 4: %d\tK: %d\tI: %d\n", vars->start_point, idx, vars->i);
	while (++idx < vars->i)
	{
		if (vars->s[idx] == '<' || vars->s[idx] == '>'
			|| vars->s[idx] == '|')
		{
			if (create_word(temp, vars, &idx))
				return (MALLOC);
		}
	}
//	printf("After:  Arr 4: %d\tK: %d\tI: %d\n", vars->start_point, idx, vars->i);
	if (idx != vars->start_point && create_word(temp, vars, &idx))
		return (MALLOC);
	return (0);
}

int	find_word(t_parser **temp, t_vars *vars)
{
	char	*word;

//	printf("Check quotes\n");
	check_quotes(vars, &vars->s[vars->i]);	// This function is used to count the number of quotes and to check
												// whether you are in a simple or double quote or in neither of those
	if (((vars->s[vars->i] == ' ' && vars->out_qts)	// This if is used to take a word, or multiple words if they are
		|| (vars->s[vars->i + 1] == '\0' && vars->s[vars->i] != ' '))) // all together and you put some special symbols into a single word
	{
		if (vars->num_qts)	// This variable is to check if your word has quotes or not
		{
			if (vars->s[vars->i + 1] == '\0' && vars->s[vars->i] != ' ')
			{
				printf("If-->I: %d\tArr 4: %d\n", vars->i, vars->start_point);
				word = ft_substr(vars->s, vars->start_point + 1, \
					vars->i - vars->start_point - 1);
			}
			else
			{
				printf("Else-->I: %d\tArr 4: %d\n", vars->i, vars->start_point);
				word = ft_substr(vars->s, vars->start_point + 1, \
					vars->i - vars->start_point - 2);
			}
			if (!word)
				return (MALLOC);
			if (add_word(temp, word))
				return (MALLOC);
		}
		else if (find_more_words(temp, vars))
			return (MALLOC);
		vars->num_qts = 0;
	}
	return (0);
}

int	parse_string(t_minishell *tokens, t_parser *all_words, char *env[], char *s)
{
	t_vars		vars;
	t_parser	*temp;

	(void)tokens;
	set_vars(&vars, s);	// Here I set the structure with all variables
	temp = all_words;	// This temp is the one used to create every word, since the pointer 'all_words'
	while (s[++vars.i])	// has always to point to the first word
	{
		if ((s[vars.i] == ' ' && vars.i == 0 && vars.out_qts)
			|| (s[vars.i - 1] == ' ' && s[vars.i] == ' ' && vars.out_qts))
			while (s[vars.i] == ' ')
				vars.i++;
		if ((s[vars.i - 1] == ' ' || vars.i == 0)
			&& s[vars.i] != ' ' && vars.out_qts)
			vars.start_point = vars.i;
		if (s[vars.i] == '$'
			&& (vars.out_qts || (!vars.out_qts && vars.dbl_qts)))
			if (check_env_var(&temp, &vars, env))
				return (MALLOC);
		if (s[vars.i] == '\0' || (s[vars.i] == ' ' && s[vars.i + 1] == '\0'))
			break ;
		if (find_word(&temp, &vars))	// Here I find the words or the multiple words to put
			return (MALLOC);				// into the all_words structure
	}
	printf("\n");
	temp = all_words;
	while (temp)	// This while is just for printing the resulted structure
	{
		printf("Temp:-->%p\n", temp);
		printf("Word:--%s--\n", temp->word);
		printf("Next:-->%p\n", temp->next);
		printf("Before:-->%p\n\n", temp->before);
		temp = temp->next;
	}
	printf("Temp: %p\n", temp);
	return (0);
}

int	parser(t_minishell *tokens, char *env[], char *string)
{
	t_parser	*all_words;

	(void)env;
	if (count_quotes(string))	// If the line you write has a impair number of quotes, the program will just stop
		return (free_tokens(&tokens, NULL, SYNTAX));
	all_words = (t_parser *)malloc(sizeof(t_parser));
	if (!all_words)
		return (free_tokens(&tokens, NULL, MALLOC));
	all_words->word = NULL;
	all_words->next = NULL;
	all_words->before = NULL;
	if (parse_string(tokens, all_words, env, string))	// Here I parse the string and separate it into words
		return (free_tokens(&tokens, NULL, MALLOC));
//	return (load_commands(tokens, all_words));	// Here I load all the words into commands in the main sucture
	return (0);
}
