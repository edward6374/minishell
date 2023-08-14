/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:51:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/14 10:17:14 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

int	join_strings(t_parser **temp, char *res)
{
	char	*join;

	join = ft_strjoin((*temp)->word, res);
	if (!join)
		return (free_pointer(res, MALLOC));
//	printf("Res: --%s--\n", res);
	printf("Join: --%s--\n", join);
	free(res);
	free((*temp)->word);
	(*temp)->word = join;
	return (0);
}

int	check_name(char *s, char *value)
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

int	take_value(t_parser **temp, t_vars *v, char *env[], char *s)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(s);
	if (ft_strncmp(s, "$?", 2))
	{
		while (env[++i])
			if (!check_name(env[i], s))
				break ;
		if (!env[i])
		{
			printf("No correspondence\n");
			return (free_pointer(s, 127));
		}
		free(s);
		s = ft_substr(env[i], len + 2, ft_strlen(env[i]) - len + 2);
	}
	if (!s || (!v->count && add_word(temp, s)))
		return (MALLOC);
	else if (!s || (v->count && join_strings(temp, s)))
		return (MALLOC);
//	printf("New value: %s\tI: %d\n", (*temp)->word, *f);
	return (0);
}

int	other_chars(t_parser **temp, t_vars *v)
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
	join_strings(temp, other);
	if ((v->s[end] == '\"' && v->s[end + 1] == '$')
		|| v->s[end] == '\'')
		v->i = end + 1;
	else if (v->s[end] == ' ' || v->s[end] == '\0')
		v->i = end;
//	if (s[end] == '\0' || s[end] == ' ')
//		*i = end - 1;
//	else if (s[end] == '\'' || s[end] == '\"')
//		*i = end + 1;
//	else
//		*i = end;
	printf("I symbols: %d\n", v->i);
	return (0);
}

char	*take_name(t_vars *v)
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

int	put_words(t_parser **temp, t_vars *v)
{
	char	*word;

	if (v->s[v->stp] == '\"')
		v->stp++;
	word = ft_substr(v->s, v->stp, v->i - v->stp);
	if (!word || add_word(temp, word))
		return (MALLOC);
	printf("Put word: --%s--\n", word);
	v->count++;
	return (0);
}

int	check_env_var(t_parser **temp, t_vars *v, char *env[])
{
	int		c;
	int		ret;
	char	*name;

	c = 0;
	v->count = -1;
	if ((v->s[v->i - 1] != ' ' || !v->oq) && put_words(temp, v))
		return (MALLOC);
	while (v->s[v->i] != ' ' && v->s[v->i] != '\0')
	{
		printf("Car: --%c--\tI: %d\n", v->s[v->i], v->i);
		if (v->s[v->i] == '$')
		{
			name = take_name(v);
			if (!name)
				return (MALLOC);
			ret = take_value(temp, v, env, name);
			if (ret == 127)
				continue ;
			else if (ret == MALLOC)
				return (MALLOC);
		}
		else if (other_chars(temp, v))
			return (MALLOC);
		if (c > 10)
			break ;
		c++;
	}
	v->stp = v->i + 1;
	return (0);
}
