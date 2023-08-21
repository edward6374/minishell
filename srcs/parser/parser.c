/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/21 21:59:49 by vduchi           ###   ########.fr       */
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

static int	find_words(t_env *env_vars, t_parser **tmp, t_vars *v)
{
	int		i;
	t_env	*env_list;

	i = v->stp - 1;
	env_list = find_env_vars(env_vars, v);
	while (++i < v->i)
	{
		printf("Loop char: --%c--\n", v->s[i]);
		check_quotes(v, &v->s[i]);
		if (v->oq && ((v->s[i + 1] == '\'' || v->s[i + 1] == '\"')
			|| (v->s[i + 1] == '\0' && v->s[i] != ' ') || v->s[i + 1] == ' ')
			&& multiple_words(tmp, &env_list, v, i + 1))
			return (MALLOC);
		else if (v->sq && words_sin_qts(tmp, v, &env_list, &i))
			return (MALLOC);
		else if (v->dq && words_dbl_qts(tmp, v, &env_list, &i))
			return (MALLOC);
	}
	printf("End loop: Char i: --%c--\tI: %d\tStart: %d\tChar idx: --%c--\n", v->s[i], i, v->stp, v->s[v->stp]);
	if ((v->s[v->i] == ' ' && v->s[v->i - 1] != ' ')
		|| (v->s[v->i] == '\0' && v->s[v->i - 1] != ' '))
		if (i - v->stp > 0 && create_word(tmp, v, &i, 1))
			return (MALLOC);
	return (0);
}

static int	parse_line(t_min *tk, t_parser *all_words, char *s)
{
	t_vars		v;
	t_parser	*tmp;

	set_vars(&v, s);
	tmp = all_words;
	while (s[v.i])
	{
		if ((s[v.i] == ' ' && v.i == 0) || (s[v.i] == ' ' && v.oq))
			while (s[v.i] == ' ')
				v.i++;
		if ((s[v.i - 1] == ' ' || v.i == 0) && s[v.i] != ' ' && v.oq)
			v.stp = v.i;
		while ((s[v.i] != ' ' || !v.oq) && s[v.i] != '\0')
			check_quotes(&v, &s[v.i++]);
		if (find_words(tk->env, &tmp, &v))
			return (free_parser(all_words, MALLOC));
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
	// return (load_commands(tk, all_words));
}
