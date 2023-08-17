/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:51:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/17 16:16:26 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

static int	put_word(t_parser **list, t_vars *v)
{
	char	*word;

	if (v->s[v->stp] == '\"')
		v->stp++;
	word = ft_substr(v->s, v->stp, v->i - v->stp);
	if (!word || add_word(list, word))
		return (MALLOC);
	printf("Put word: --%s--\n", word);
	v->count++;
	return (0);
}

static int	join_strings(t_parser **list, char *res)
{
	char	*join;

	join = ft_strjoin((*list)->word, res);
	if (!join)
		return (free_pointer(res, MALLOC));
//	printf("Res: --%s--\n", res);
	printf("Join: --%s--\n", join);
	free(res);
	free((*list)->word);
	(*list)->word = join;
	return (0);
}

static int	check_name(char *s, char *value)
{
	int	i;

	i = 0;
	while (s[i] && value[i] && s[i] == value[i])
	{
//		printf("First: %c\tSecond: %c\n", s[i], value[i]);
		i++;
	}
	if (value[i] == '\0')
		return (0);
	return (1);
}

static int	other_chars(t_parser **list, t_vars *v)
{
	int		end;
	int		start;
	char	c;
	char	*other;
	int		counter;

	printf("Double: %d\n", v->dq);
	if (v->s[v->i] == '\'' || v->s[v->i] == '\"')
		c = v->s[v->i++];
	else
		c = '\0';
	end = v->i;
	start = v->i;
	printf("C: %c\tStart: %d\n", c, start);
	counter = 0;
	while ((c != '\0' && v->s[end] != c)
		|| (c == '\0' && v->s[end] != c && v->s[end] != ' '))
	{
		printf("Loop char: %c\tEnd: %d\n", v->s[end], end);
		if (v->s[end] == '\"' && v->s[end + 1] == '$')
			break ;
		if (counter > 15)
			break ;
		counter++;
		end++;
	}
	other = ft_substr(v->s, start, end - start);
	if (!other)
		return (MALLOC);
	printf("Other: --%s--\n", other);
	join_strings(list, other);
	if ((v->s[end] == '\"' && v->s[end + 1] == '$')
		|| v->s[end] == '\'')
	{
		printf("Here End: %d\tChar end: %c\n", end, v->s[end]);
		end++;
		if (v->s[end] == '\"')
			end++;
		v->i = end;
	}
	else if (v->s[end] == ' ' || v->s[end] == '\0')
		v->i = end;
//	if (s[end] == '\0' || s[end] == ' ')
//		*i = end - 1;
//	else if (s[end] == '\'' || s[end] == '\"')
//		*i = end + 1;
//	else
//		*i = end;
	printf("I symbols: %d\tChar i: %c\n", v->i, v->s[v->i]);
	return (0);
}

static int	take_value(t_min *tk, t_parser **list, t_vars *v, char *s)
{
	int		i;
	int		len;
	t_env	*tmp;

	i = -1;
	len = ft_strlen(s);
	if (ft_strncmp(s, "$?", 2))
	{
		tmp = tk->env;
		while (tmp)
		{
			if (!check_name(tmp->name, s))
				break ;
			tmp = tmp->next;
		}
		if (!tmp)
		{
			printf("No correspondence\n");
			return (free_pointer(s, 127));
		}
		free(s);
		s = ft_substr(tmp->value, 0, ft_strlen(tmp->value));
	}
	printf("S: %s\n", s);
	if (!s || (!v->count && add_word(list, s)))
		return (MALLOC);
	else if (!s || (v->count && join_strings(list, s)))
		return (MALLOC);
	return (0);
}

static char	*take_name(t_vars *v)
{
	int		end;
	int		start;
	char	*name;

	start = v->i + 1;
	if (v->s[v->i] == '$' && v->s[v->i + 1] == '?')
		start = v->i++;
	end = v->i + 1;
	while ((v->s[end] >= 'a' && v->s[end] <= 'z')
		|| (v->s[end] >= 'A' && v->s[end] <= 'Z'))
		end++;
	printf("Start: %d\tChar start: %c\tEnd: %d\tChar end:%c\n", start, v->s[start], end, v->s[end]);
	name = ft_substr(v->s, start, end - start);
	if (!name)
		return (NULL);
	printf("Name: --%s--\n", name);
	if (v->s[end] == '\"')
	{
		v->dq = 0;
		v->nq = 0;
		v->i = end + 1;
	}
	else
		v->i = end;
	v->count++;
	return (name);
}

int	check_env_var(t_min *tk, t_parser **list, t_vars *v)
{
	int		c;
	int		err;
	char	*name;

	c = 0;
	v->count = -1;
	if ((v->s[v->i - 1] != ' ' || !v->oq) && put_word(list, v))
		return (MALLOC);
	while (v->s[v->i] != ' ' && v->s[v->i] != '\0')
	{
		printf("Car: --%c--\tI: %d\n", v->s[v->i], v->i);
		if (v->s[v->i] == '$')
		{
			name = take_name(v);
			if (!name)
				return (MALLOC);
			err = take_value(tk, list, v, name);
			if (err == 127)
				continue ;
			else if (err == MALLOC)
				return (MALLOC);
		}
		else if (other_chars(list, v))
			return (MALLOC);
		if (c > 10)
			break ;
		c++;
	}
	v->stp = v->i + 1;
	return (0);
}
