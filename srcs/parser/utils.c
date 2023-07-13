/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:50:22 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/13 15:37:27 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/parser.h"

void	check_quotes(t_vars *vars, char *c)
{
	if (*c == '\"' && *(c + 1) == '$')
		return ;
	if (*c == '\'' && vars->sin_qts == 0 && vars->dbl_qts == 0)
	{
		vars->sin_qts = 1;
		vars->num_qts++;
	}
	else if (*c == '\'' && vars->sin_qts == 1)
	{
		vars->sin_qts = 0;
		vars->num_qts++;
	}
	else if (*c == '\"' && vars->dbl_qts == 0 && vars->sin_qts == 0)
	{
		vars->dbl_qts = 1;
		vars->num_qts++;
	}
	else if (*c == '\"' && vars->dbl_qts == 1)
	{
		vars->dbl_qts = 0;
		vars->num_qts++;
	}
	if (vars->sin_qts == 0 && vars->dbl_qts == 0 \
		&& *c != '\'' && *c != '\"')
		vars->out_qts = 1;
	else
		vars->out_qts = 0;
//	printf("Char %c\tArr 0: %d\tArr 1: %d\tArr 2: %d\tArr 3:%d\tArr 4: %d\n", *c, arr[0], arr[1], arr[2], arr[3], arr[4]);
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
