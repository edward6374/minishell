/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/13 19:39:51 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

void	set_vars(t_vars *vars, char *str)
{
	vars->i = -1;
	vars->sin_qts = 0;
	vars->dbl_qts = 0;
	vars->out_qts = 1;
	vars->num_qts = 0;
	vars->start_point = 0;
	vars->str = str;
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

int	create_word(t_parser **temp, t_vars *vars, int *idx)
{
	int		len;
	int		start;
	int		redir;
	char	*word;

	start = vars->start_point;
	if (*idx == vars->start_point)
		len = 1;
	else
	{
		len = *idx - vars->start_point;
		if (len == 1 && ((vars->str[*idx - 1] == '<' && vars->str[*idx] == '<')
			|| (vars->str[*idx - 1] == '>' && vars->str[*idx] == '>'))
			&& vars->str[*idx + 1] != '\0')
			len++;
		if (vars->str[*idx + 1] == '\0' && vars->str[*idx] != ' ')
			len++;
	}
	printf("Idx: %d\tLen: %d\tStart: %d\tCar: %c\n", *idx, len, start, vars->str[*idx]);
	word = ft_substr(vars->str, start, len);
	if (!word || add_word(temp, word))
		return (MALLOC);
//	printf("C Start + Len: %c\tC + 1: %c\n", vars->str[start + len], vars->str[start + len + 1]);
	if (*idx != vars->start_point
		&& vars->str[start + len] != '\0' && vars->str[start + len] != ' ')
	{
		redir = 1;
		if ((vars->str[*idx] == '<' && vars->str[*idx + 1] == '<')
		|| (vars->str[*idx] == '>' && vars->str[*idx + 1] == '>'))
		{
			(*idx)++;
			redir++;
		}
		printf("Here\n");
		word = ft_substr(vars->str, start + len, redir);
		if (!word || add_word(temp, word))
			return (MALLOC);
	}
	vars->start_point = *idx + 1;
	return (0);
}

int	find_more_words(t_parser **temp, t_vars *vars)
{
	int	idx;

	idx = vars->start_point - 1;
	printf("Before: Arr 4: %d\tK: %d\tI: %d\n", vars->start_point, idx, vars->i);
	while (++idx < vars->i)
	{
		if (vars->str[idx] == '<' || vars->str[idx] == '>'
			|| vars->str[idx] == '|')
		{
			printf("If idx: %d\tC: %c\n", idx, vars->str[idx]);
			if (vars->str[idx - 1] == ' '
				&& ((vars->str[idx] == '<' && vars->str[idx + 1] == '<')
				|| (vars->str[idx] == '>' && vars->str[idx + 1] == '>')))
			{
				printf("One more\n");
				idx++;
			}
			if (create_word(temp, vars, &idx))
				return (MALLOC);
//			if (idx == vars->start_point)
//			{
//				if (create_word(temp, vars, &vars->start_point, 1))
//					return (MALLOC);
//				vars->start_point = idx + 1;
//				continue ;
//			}
//			if (create_word(temp, vars->str, &vars->start_point, \
//				idx - vars->start_point))
//				return (MALLOC);
//			if (create_word(temp, vars->str, &idx, 1))
//				return (MALLOC);
//			vars->start_point = idx + 1;
		}
	}
	printf("After:  Arr 4: %d\tK: %d\tI: %d\n", vars->start_point, idx, vars->i);
	if (idx != vars->start_point && create_word(temp, vars, &idx))
		return (MALLOC);
//	printf("Word: ---%s---\n", (*temp)->word);
	return (0);
}

int	find_word(t_parser **temp, t_vars *vars)
{
	char	*word;

	check_quotes(vars, &vars->str[vars->i]);	// This function is used to count the number of quotes and to check
												// whether you are in a simple or double quote or in neither of those
	if (((vars->str[vars->i] == ' ' && vars->out_qts)	// This if is used to take a word, or multiple words if they are
		|| (vars->str[vars->i + 1] == '\0' && vars->str[vars->i] != ' '))) // all together and you put some special symbols into a single word
	{
		if (vars->num_qts)	// This variable is to check if your word has quotes or not
		{
			if (vars->str[vars->i + 1] == '\0' && vars->str[vars->i] != ' ')
			{
				printf("If-->I: %d\tArr 4: %d\n", vars->i, vars->start_point);
				word = ft_substr(vars->str, vars->start_point + 1, \
					vars->i - vars->start_point - 1);
			}
			else
			{
				printf("Else-->I: %d\tArr 4: %d\n", vars->i, vars->start_point);
				word = ft_substr(vars->str, vars->start_point + 1, \
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

/*
int	if_conds(t_vars *vars, char *str)
{
	if (str[vars->i] == ' ' && vars->i == 0 && vars->out_qts) 	// This if is to check whether you have one or multiple spaces
		while (str[vars->i] == ' ')								// at the beginning of the string
			vars->i++;
	if (str[vars->i - 1] == ' ' && str[vars->i] == ' ' && vars->out_qts)	// This if is to check whether you have one
		return (1);															// or multiple spaces in the middle of the string
	else if ((str[vars->i - 1] == ' ' || vars->i == 0)	// This if is to set the variable vars->start_point to the
		&& str[vars->i] != ' ' && vars->out_qts)		// first character of every word
		vars->start_point = vars->i;
	return (0);
}
*/

int	parse_string(t_minishell *tokens, t_parser *all_words, char *env[], char *str)
{
	t_vars		vars;
	t_parser	*temp;

	(void)tokens;
	set_vars(&vars, str);	// Here I set the structure with all variables
	temp = all_words;	// This temp is the one used to create every word, since the pointer 'all_words'
	while (str[++vars.i])	// has always to point to the first word
	{
//		if (if_conds(&vars, str))
//			continue ;
//		printf("Loop\n");
		if ((str[vars.i] == ' ' && vars.i == 0 && vars.out_qts)
			|| (str[vars.i - 1] == ' ' && str[vars.i] == ' ' && vars.out_qts))
			while (str[vars.i] == ' ')
				vars.i++;
		if ((str[vars.i - 1] == ' ' || vars.i == 0)
			&& str[vars.i] != ' ' && vars.out_qts)
			vars.start_point = vars.i;
		if (str[vars.i] == '$'
			&& (vars.out_qts || (!vars.out_qts && vars.dbl_qts)))
			if (check_env_var(&temp, &vars, env))
				return (MALLOC);
		if (str[vars.i] != '\0' && find_word(&temp, &vars))	// Here I find the words or the multiple words to put
			return (MALLOC);				// into the all_words structure
	}
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
//	return (load_commands(tokens, all_words));	// Here I load all the words into commands in the main structure
	return (0);
}
