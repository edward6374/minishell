/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/21 10:28:48 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// TODO
// arreglar esta funcion de exit_status y ponerla en la ejecucion de los hijos

int	check_for_exit_status(t_min *tk, t_parser *all_words)
{
//	t_check		dt;
	t_parser	*p;

	(void)tk;
//	p = all_words;
//	while (p)
//	{
//		dt.len = ft_strlen(p->word);
//		if (ft_strncmp(p->word, "$?", 3) && (ft_strnstr(p->word, "$?", dt.len)))
//		{
//			dt.len = dt.len - ft_strlen(ft_strnstr(p->word, "$?", dt.len));
//			dt.new = ft_strjoin(ft_substr(p->word, 0, dt.len),
//					ft_itoa(tk->exit_value));
//			if (!dt.new)
//				return (free_parser(all_words, MALLOC));
//			dt.new = ft_strjoin(dt.new, ft_strnstr(p->word, "$?",
//						ft_strlen(p->word)) + 2);
//			if (!dt.new)
//				return (free_parser(all_words, free_pointer(dt.new, MALLOC)));
//			free(p->word);
//			p->word = dt.new;
//		}
//		p = p->next;
//	}
	p = all_words;
	while (p)    // This while is just for printing the resulted structure
	{
		printf("Temp:-->%p\n", p);
		printf("Word:--%s--\n", p->word);
		printf("Next:-->%p\n", p->next);
		printf("Before:-->%p\n\n", p->before);
		p = p->next;
	}
	printf("Temp: %p\n", p);
	return (0);
}

int	parse_line(t_min *tk, t_parser *all_words, char *s)
{
	t_vars		v;
	t_parser	*tmp;

	set_vars(&v, s);
	tmp = all_words;
	while (s[v.i])
	{
//		printf("I = -%c-\tI - 1 = -%c-\n", s[v.i], s[v.i - 1]);
//		printf("Sq: %d\tDq: %d\tOq: %d\n", v.sq, v.dq, v.oq);
		if ((s[v.i] == ' ' && v.i == 0) || (s[v.i] == ' ' && v.oq))
			while (s[v.i] == ' ')
				v.i++;
		if ((s[v.i - 1] == ' ' || v.i == 0) && s[v.i] != ' ' && v.oq)
			v.stp = v.i;
		while ((s[v.i] != ' ' || !v.oq) && s[v.i] != '\0')
		{
			check_quotes(&v, &s[v.i]);
			v.i++;
			printf("Char: --%c--\tI: %d\n", s[v.i], v.i);
			printf(RED "C: %c\tSq: %d\tDq: %d\tOq: %d\tNq: %d\n" NO_COLOR, s[v.i], v.sq, v.dq, v.oq, v.nq);
		}
		printf("\n");
		if (find_words(tk->env, &tmp, &v))
			return (free_parser(all_words, MALLOC));
//		check_quotes(&v, v.s[v.i]);
//		if (s[v.i] == '$' && (v.oq || (!v.oq && v.dq)))
//			if (take_words_with_quotes(&tmp, &v) || check_env_var(tk, &tmp, &v))
//				return (free_parser(all_words, MALLOC));
//		if (s[v.i] == '\0')
//			break ;
//		if (find_words(&tmp, &v))
//			return (free_parser(all_words, MALLOC));
	}
	return (check_for_exit_status(tk, all_words));
}

int	parser(t_min *tk, char *line)
{
	t_parser	*all_words;

	if (count_quotes(line))
		return (SYNTAX);
	all_words = (t_parser *)malloc(sizeof(t_parser));
	if (!all_words)
		return (free_all(tk, MALLOC));
	all_words->word = NULL;
	all_words->next = NULL;
	all_words->before = NULL;
	if (parse_line(tk, all_words, line))
		return (free_all(tk, MALLOC));
	return (0);
//	return (load_commands(tk, all_words));
}
