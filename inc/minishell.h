/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:14:15 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/04 16:09:49 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "pipes.h"
# include "built-ins.h"
# include "parser.h"
# include "../readline/library/include/readline/readline.h"
# include "../readline/library/include/readline/history.h"

enum
{
	MALLOC = 1,
	SYNTAX
};

const static char	*g_error_array[] = {
	"Malloc error", \
	"Syntax error", \
};

int		d_key(void);
int		end_program(char **string, int error);

void	siginthandler(int sig);
void	free_double(char ***dbl);
void	free_tokens(t_minishell **tokens);

char	*ft_find_path(char *env[]);

#endif
