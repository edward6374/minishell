/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 18:15:30 by gdominic          #+#    #+#             */
/*   Updated: 2023/06/06 20:10:10 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipes.h"

t_command	*add_elem(char *cmd, char **args)
{
	t_command	*tok;

	tok = (t_command *)malloc(sizeof(t_command));
	if (!tok)
		return (NULL);
	tok->cmd = ft_strdup(cmd);
	tok->args = args;
	tok->next = NULL;
	return (tok);
}

void	minishell(t_minishell *tokens, char *env[], char *str)
{
	char		**matrix;

	if (!str)
		return ;
	matrix = ft_split(str, ' ');
	if (!matrix)
	{
		free(tokens);
		perror("Malloc error #1");
		exit (1);
	}
	tokens->command = add_elem(matrix[0], matrix);
	if (!tokens->command)
	{
		free(tokens);
//		free(matrix);	// free a double pointer
		perror("Malloc error #2");
		exit (1);
	}
	pipes(tokens, env);
}

