/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:51:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/14 14:38:21 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

int	join_strings(t_parser **temp, char *res)
{
	char	*join;

	join = ft_strjoin((*temp)->word, res);
	if (!join)
	{
		free(res);
		return (MALLOC);
	}
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
//	printf("Check\tEnv: ---%s---\tVar: ---%s---\n", s, value);
	while (s[i] && value[i] && s[i] == value[i])
	{
//		printf("First: %c\tSecond: %c\n", s[i], value[i]);
		i++;
	}
	if (value[i] == '\0')
		return (0);
	return (1);
}

int	take_value(t_parser **temp, t_vars *vars, char *env[], char *s)
{
	int		i;
	int		len;

	i = -1;
	while (env[++i])
		if (!check_name(env[i], s))
			break ;
	if (!env[i])
	{
		printf("No correspondence\n");
		free(s);
		return (127);
	}
	len = ft_strlen(s);
	free(s);
	s = ft_substr(env[i], len + 2, ft_strlen(env[i]) - len + 2);
	if (!s)
		return (MALLOC);
	if (!vars->count && add_word(temp, s))
		return (MALLOC);
	else if (vars->count && join_strings(temp, s))
		return (MALLOC);
//	printf("New value: %s\tI: %d\n", (*temp)->word, *f);
	return (0);
}

int	other_chars(t_parser **temp, t_vars *vars)
{
	int		end;
	int		start;
	char	c;
	char	*other;
	int		counter;

	printf("Double: %d\n", vars->dbl_qts);
	if (vars->s[vars->i] == '\'' || vars->s[vars->i] == '\"')
		c = vars->s[vars->i++];
	else
		c = '\0';
	end = vars->i;
	start = vars->i;
	printf("C: %c\tStart: %d\n", c, start);
	counter = 0;
	while ((c != '\0' && vars->s[end] != c)
		|| (c == '\0' && vars->s[end] != c && vars->s[end] != ' '))
	{
		printf("Loop char: %c\tEnd: %d\n", vars->s[end], end);
		if (vars->s[end] == '\"' && vars->s[end + 1] == '$')
			break ;
		if (counter > 15)
			break ;
		counter++;
		end++;
	}
	other = ft_substr(vars->s, start, end - start);
	if (!other)
		return (MALLOC);
	printf("Other: --%s--\n", other);
	join_strings(temp, other);
	if ((vars->s[end] == '\"' && vars->s[end + 1] == '$')
		|| vars->s[end] == '\'')
		vars->i = end + 1;
	else if (vars->s[end] == ' ' || vars->s[end] == '\0')
		vars->i = end;
//	if (s[end] == '\0' || s[end] == ' ')
//		*i = end - 1;
//	else if (s[end] == '\'' || s[end] == '\"')
//		*i = end + 1;
//	else
//		*i = end;
	printf("I symbols: %d\n", vars->i);
	return (0);
}

char	*take_name(t_vars *vars)
{
	int		end;
	int		start;
	char	*name;

	end = vars->i + 1;
	start = vars->i + 1;
	while ((vars->s[end] >= 'a' && vars->s[end] <= 'z')
		|| (vars->s[end] >= 'A' && vars->s[end] <= 'Z'))
		end++;
	name = ft_substr(vars->s, start, end - start);
	if (!name)
		return (NULL);
//	printf("End: --%c--\n", vars->s[end]);
	if (vars->s[end] == '\"')
	{
		printf("Change if\n");
		vars->dbl_qts = 0;
		vars->num_qts = 0;
		vars->i = end + 1;
	}
	else
	{
		printf("Change else\n");
		vars->i = end;
	}
	printf("Name: --%s--\t", name);
	printf("Car : %c\tTake name i: %d\n", vars->s[vars->i], vars->i);
	vars->count++;
	return (name);
}

int	put_words(t_parser **temp, t_vars *vars)
{
	char	*word;

	if (vars->s[vars->start_point] == '\"')
		vars->start_point++;
	word = ft_substr(vars->s, vars->start_point, vars->i - vars->start_point);
	if (!word || add_word(temp, word))
		return (MALLOC);
	printf("Put word: --%s--\n", word);
	vars->count++;
	return (0);
}

int	check_env_var(t_parser **temp, t_vars *vars, char *env[])
{
	int		ret;
	int		c;
	char	*name;

	c = 0;
	vars->count = -1;
	if ((vars->s[vars->i - 1] != ' ' || !vars->out_qts) && put_words(temp, vars))
		return (MALLOC);
	while (vars->s[vars->i] != ' ' && vars->s[vars->i] != '\0')
	{
		printf("Car: --%c--\tI: %d\n", vars->s[vars->i], vars->i);
		if (vars->s[vars->i] == '$')
		{
			name = take_name(vars);
			if (!name)
				return (MALLOC);
			ret = take_value(temp, vars, env, name);
			if (ret == 127)
				continue ;
			else if (ret == MALLOC)
				return (MALLOC);
		}
		else if (other_chars(temp, vars))
			return (MALLOC);
		if (c > 10)
			break ;
		c++;
	}
	vars->start_point = vars->i + 1;
	return (0);
}
