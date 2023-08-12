/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/12 18:18:25 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

// TODO
// arreglar esta funcion de exit_status y ponerla en la ejecucion de los hijos

int	check_for_exit_status(t_min *tk, t_parser *all_words)
{
	int			len;
	char		*new;
	t_parser	*p;

	p = all_words;
	while (p)
	{
		len = ft_strlen(p->word);
		if (ft_strncmp(p->word, "$?", 3) && (ft_strnstr(p->word, "$?", len)))
		{
			len = len - ft_strlen(ft_strnstr(p->word, "$?", len));
			new = ft_strjoin(ft_substr(p->word, 0, len), \
				ft_itoa(tk->exit_value));
			if (!new)
				return (free_parser(all_words, MALLOC));
			new = ft_strjoin(new, ft_strnstr(p->word, "$?", \
				ft_strlen(p->word)) + 2);
			if (!new)
				return (free_parser(all_words, free_pointer(new, MALLOC)));
			free(p->word);
			p->word = new;
		}
		p = p->next;
	}
	p = all_words;
	while (p)    // This while is just for printing the resulted structure
	{
		printf("Temp:-->%p\n", p);
		printf("Word:--%s--\n", p->word);
//		printf("Word point:--%p--\n", p->word);
		printf("Next:-->%p\n", p->next);
		printf("Before:-->%p\n\n", p->before);
		p = p->next;
	}
	printf("Temp: %p\n", p);
	return (0);
}

int	parse_string(t_min *tk, t_parser *all_words, char *env[], char *s)
{
	t_vars		v;
	t_parser	*temp;

	set_vars(&v, s);  // Here I set the structure with all variables
	temp = all_words;    // This temp is the one used to create every word, since the pointer 'all_words'
	while (s[++v.i])  // has always to point to the first word
	{
		if ((s[v.i] == ' ' && v.i == 0 && v.oq)
				|| (s[v.i - 1] == ' ' && s[v.i] == ' ' && v.oq))
			while (s[v.i] == ' ')
				v.i++;
		if ((s[v.i - 1] == ' ' || v.i == 0)
			&& s[v.i] != ' ' && v.oq)
			v.stp = v.i;
		if (s[v.i] == '$' && (v.oq || (!v.oq && v.dq)))
			if (check_env_var(&temp, &v, env))
				return (free_parser(all_words, MALLOC));
		if (s[v.i] == '\0')
			break ;
		if (find_word(&temp, &v)) // Here I find the words or the multiple words to put into the all_words structure
			return (free_parser(all_words, MALLOC));
	}
	printf("\n");
	return (check_for_exit_status(tk, all_words));
}

int	parser(t_min *tk, char *env[], char *string)
{
	t_parser	*all_words;

	if (count_quotes(string))    // If the line you write has a impair number of quotes, the program will just stop
		return (free_all(tk, SYNTAX));
	all_words = (t_parser *)malloc(sizeof(t_parser));
	if (!all_words)
		return (free_all(tk, MALLOC));
	all_words->word = NULL;
	all_words->next = NULL;
	all_words->before = NULL;
	if (parse_string(tk, all_words, env, string))    // Here I parse the string and separate it into words
		return (free_all(tk, MALLOC));
	return (load_commands(tk, all_words));           // Here I load all the words into commands in the main sucture
}
