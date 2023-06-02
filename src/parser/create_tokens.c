/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:56:41 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/02 19:48:44 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	load_commands(t_minishell *tokens, char **split)
{
	int	i;
	int	after_pipe;

	i = -1;
	if (split[0][0] == '|' && split[0][1] == '\0')
		return (1); //Qui si deve ritornare un errore
	while (split[++i])
	{
	}
}
