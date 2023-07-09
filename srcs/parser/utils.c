/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:50:22 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/08 18:01:32 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

void	check_quotes(char *c, int *arr)
{
	if (*c == '\'' && arr[0] == 0 && arr[1] == 0)
	{
		arr[0] = 1;
		arr[3]++;
	}
	else if (*c == '\'' && arr[0] == 1)
	{
		arr[0] = 0;
		arr[3]++;
	}
	else if (*c == '\"' && arr[1] == 0 && arr[0] == 0)
	{
		arr[1] = 1;
		arr[3]++;
	}
	else if (*c == '\"' && arr[1] == 1)
	{
		arr[1] = 0;
		arr[3]++;
	}
	if (arr[0] == 0 && arr[1] == 0 \
		&& *c != '\'' && *c != '\"')
		arr[2] = 1;
	else
		arr[2] = 0;
}

char	**free_my_split(char **split, int **len_words, int i)
{
	while (--i >= 0)
		free(split[i]);
	free(split);
	free(*len_words);
	*len_words = NULL;
	return (NULL);
}

int	free_split_with_index(char **split, int index, int i)
{
	while (--index >= 0)
	{
		if (index == i)
			continue ;
		free(split[i]);
	}
	free(split);
	split = NULL;
	return (1);
}

int	free_split(char **split, int i)
{
	while (--i >= 0)
		free(split[i]);
	free(split);
	return (1);
}

int	free_int_arr(int **len_words)
{
	free(*len_words);
	*len_words = NULL;
	return (1);
}
