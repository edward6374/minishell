/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:01:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/06 16:29:54 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

int	update_string(char **str)
{
	char	*new;

	new = ft_strdup(*str);
	if (!new)
		return (1);
	free(*str);
	*str = ft_strdup(new);
	if (!*str)
	{
		free(new);
		new = NULL;
		return (1);
	}
	return (0);
}

void	modify_string(char *str, int *quote, int new_value, int *index)
{
	int	copy;

	copy = *index;
	while (str[copy])
	{
		str[copy] = str[copy + 1];
		copy++;
	}
	*quote = new_value;
	(*index)--;
}

void	check_string(char *str, int *quotes, int *j)
{
	if (str[*j] == '\'' && quotes[0] == 0 && quotes[1] == 0)
		modify_string(str, &quotes[0], 1, j);
	else if (str[*j] == '\'' && quotes[0] == 1 && quotes[1] == 0)
		modify_string(str, &quotes[0], 0, j);
	else if (str[*j] == '\"' && quotes[0] == 0 && quotes[1] == 0)
		modify_string(str, &quotes[1], 1, j);
	else if (str[*j] == '\"' && quotes[0] == 0 && quotes[1] == 1)
		modify_string(str, &quotes[1], 0, j);
}

int	correct_quotes(char **split)
{
	int	i;
	int	j;
	int	quotes[2];

	i = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
			check_string(split[i], quotes, &j);
//		if(update_string(&split[i]))
//			return (free_split_with_index(split, index, i));
	}
	i = -1;
	while (split[++i])
		printf("Word modified:%s-->\n", split[i]);
	return (0);
}

int	count_quotes(char *string)
{
	int	i;
	int	q[2];

	i = -1;
	q[0] = 0;
	q[1] = 0;
	while (string[++i])
	{
		if (string[i] == '\'')
			q[0]++;
		else if (string[i] == '\"')
			q[1]++;
	}
	if (q[0] % 2 == 0 && q[1] % 2 == 0)
		return (0);
	return (1);
}
