/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:17:24 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/08 18:01:46 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipes.h"

int	pipes(t_minishell *tokens, char *env[])
{
	int			res;
	t_command	*tmp;

	res = 0;
	tmp = tokens->command;
	while (tmp)
	{
	    printf("Command: %s\n", tmp->cmd);
	    printf("Arguments:\n");
	    char **args = tmp->args;
		int i = -1;
	    while (args[++i]) 
		{
	        printf(" - %s\n", args[i]);
//	        args++;
	    }
//	    printf("P: %p\tValue 1: %s\tValue 2: %s\n", tmp->args, tmp->args[0], tmp->args[1]);
	    tmp = tmp->next;  // Avanzar al siguiente nodo de la lista
	}
//	if (check_command(tokens) == 0)
//		res = run_commands(tokens->command, env);
//	else
//		ft_putstr_error("BUILTIN pending manage\n");
//	printf("res: %d\n", res);
	res = run_commands(tokens, env);
	return (0);
}
