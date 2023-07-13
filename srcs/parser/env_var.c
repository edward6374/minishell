/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:51:57 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/13 17:01:52 by vduchi           ###   ########.fr       */
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
//	printf("Join: --%s--\n", join);
	free(res);
	free((*temp)->word);
	(*temp)->word = join;
	return (0);
}

int	check_name(char *str, char *value)
{
	int	i;

	i = 0;
//	printf("Check\tEnv: ---%s---\tVar: ---%s---\n", str, value);
	while (str[i] && value[i] && str[i] == value[i])
	{
//		printf("First: %c\tSecond: %c\n", str[i], value[i]);
		i++;
	}
	if (value[i] == '\0')
		return (0);
	return (1);
}

int	take_value(t_parser **temp, char *env[], char *str, int count)
{
	int		i;
	int		len;

	i = -1;
	while (env[++i])
		if (!check_name(env[i], str))
			break ;
	if (!env[i])
	{
		printf("No correspondence\n");
		free(str);
		return (127);
	}
	len = ft_strlen(str);
	free(str);
	str = ft_substr(env[i], len + 2, ft_strlen(env[i]) - len + 2);
	if (!str)
		return (MALLOC);
	if (!count && add_word(temp, str))
		return (MALLOC);
	else if (count && join_strings(temp, str))
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

	if (vars->str[vars->i] == '\'' || vars->str[vars->i] == '\"')
		c = vars->str[vars->i++];
	else
		c = '\0';
	end = vars->i - 1;
	start = vars->i;
	printf("C: %c\tStart: %d\n", c, start);
	while ((c != '\0' && vars->str[++end] != c)
		|| (c == '\0' && vars->str[end] != c && vars->str[end] != ' '))
	{
		printf("Loop char: %c\tEnd: %d\n", vars->str[end], end);
		if (vars->str[end] == '\"' && vars->str[end + 1] == '$')
			break ;
	}
	other = ft_substr(vars->str, start, end - start);
	if (!other)
		return (MALLOC);
	printf("Other: --%s--\n", other);
	join_strings(temp, other);
	if ((vars->str[end] == '\"' && vars->str[end + 1] == '$')
		|| vars->str[end] == '\'')
		vars->i = end + 1;
	else if (vars->str[end] == ' ' || vars->str[end] == '\0')
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

char	*take_name(t_vars *vars, int *count)
{
	int		end;
	int		start;
	char	*name;

	end = vars->i + 1;
	start = vars->i + 1;
	while ((vars->str[end] >= 'a' && vars->str[end] <= 'z')
		|| (vars->str[end] >= 'A' && vars->str[end] <= 'Z'))
		end++;
	name = ft_substr(vars->str, start, end - start);
	if (!name)
		return (NULL);
	if (vars->dbl_qts && vars->str[end] == '\"')
	{
		vars->dbl_qts = 0;
		vars->i = end + 1;
	}
	else
	{
		printf("Here\n");
		vars->i = end;
	}
	printf("Name: --%s--\t", name);
	printf("Car : %c\tTake name: %d\n", vars->str[vars->i], vars->i);
	(*count)++;
	return (name);
}

int	check_env_var(t_parser **temp, t_vars *vars, char *env[])
{
	int		ret;
	int		count;
	char	*name;

	count = -1;
	if (vars->str[vars->i] == '\"')
		vars->i++;
	while (vars->str[vars->i] != ' ' && vars->str[vars->i] != '\0')
	{
		if (vars->str[vars->i] == '$')
		{
			name = take_name(vars, &count);
			if (!name)
				return (MALLOC);
			ret = take_value(temp, env, name, count);
			if (ret == 127)
				continue ;
			else if (ret == MALLOC)
				return (MALLOC);
		}
		else if (other_chars(temp, vars))
			return (MALLOC);
	}
	vars->start_point = vars->i + 1;
	return (0);
	/*
	while (s[(*i + 1)] != ' ' && s[*i + 1] != '\0')
	{
		printf("Car : %c\tBefore: %c\tI: %d\n", s[*i], s[*i - 1], *i);
		if (s[*i] != '$' && !(s[*i] == '\"' && s[*i + 1] == '$'))
		{
			if (with_symbols(temp, s, i))
				return (MALLOC);
		}
		else
		{
			name = take_name(s, i, &count);
			if (!name)
				return (MALLOC);
			ret = take_value(temp, env, name, count);
			if (ret == 127)
				continue ;
			else if (ret == MALLOC)
				return (MALLOC);
		}
	}
//	printf("End I: %d\tLast: %c\n", *i, s[*i]);
	*/
}
