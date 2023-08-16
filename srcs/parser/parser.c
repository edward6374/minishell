/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 16:31:04 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

// TODO
// arreglar esta funcion de exit_status y ponerla en la ejecucion de los hijos

int	check_for_exit_status(t_min *tk, t_parser *all_words)
{
	t_check		dt;
	t_parser	*p;

	p = all_words;
	while (p)
	{
		dt.len = ft_strlen(p->word);
		if (ft_strncmp(p->word, "$?", 3) && (ft_strnstr(p->word, "$?", dt.len)))
		{
			dt.len = dt.len - ft_strlen(ft_strnstr(p->word, "$?", dt.len));
			dt.new = ft_strjoin(ft_substr(p->word, 0, dt.len),
					ft_itoa(tk->exit_value));
			if (!dt.new)
				return (free_parser(all_words, MALLOC));
			dt.new = ft_strjoin(dt.new, ft_strnstr(p->word, "$?",
						ft_strlen(p->word)) + 2);
			if (!dt.new)
				return (free_parser(all_words, free_pointer(dt.new, MALLOC)));
			free(p->word);
			p->word = dt.new;
		}
		p = p->next;
	}
	p = all_words;
	return (0);
}

int	parse_line(t_min *tk, t_parser *all_words, char *s)
{
	t_vars		v;
	t_parser	*temp;

	set_vars(&v, s);
	temp = all_words;
	while (s[++v.i])
	{
		if ((s[v.i] == ' ' && v.i == 0 && v.oq) || (s[v.i - 1] == ' '
				&& s[v.i] == ' ' && v.oq))
			while (s[v.i] == ' ')
				v.i++;
		if ((s[v.i - 1] == ' ' || v.i == 0) && s[v.i] != ' ' && v.oq)
			v.stp = v.i;
		if (s[v.i] == '$' && (v.oq || (!v.oq && v.dq)))
			if (check_env_var(tk, &temp, &v))
				return (free_parser(all_words, MALLOC));
		if (s[v.i] == '\0')
			break ;
		if (find_word(&temp, &v))
			return (free_parser(all_words, MALLOC));
	}
	return (check_for_exit_status(tk, all_words));
}

int	parser(t_min *tk, char *line)
{
	t_parser	*all_words;

	if (count_quotes(line))
		return (free_all(tk, SYNTAX));
	all_words = (t_parser *)malloc(sizeof(t_parser));
	if (!all_words)
		return (free_all(tk, MALLOC));
	all_words->word = NULL;
	all_words->next = NULL;
	all_words->before = NULL;
	if (parse_line(tk, all_words, line))
		return (free_all(tk, MALLOC));
	return (load_commands(tk, all_words));
}
