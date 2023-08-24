/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:14:15 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/24 13:19:22 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "struct.h"
# include "execute.h"
# include "history.h"
# include "libft.h"
# include "parser.h"
# include "readline.h"

/* ---			Take_env.c			--- */
int		take_env(t_min *tk, char *env[]);

/* ---			Utils.c				--- */
void	set_term(void);
int		d_key(t_min **tk);
int		exit_error(const char *str, int i);
int		end_program(char **line, int error);
char	*ft_find_path(char *env[]);

/* ---			Free_funcs.c			--- */
void	free_err_f(char **line);
int		free_pointer(void *pt, int out);
int		free_double_int(char **old, int i);
void	free_double_void(char **old);
char	**free_double_char(char **old, int i);

/* ---			Free_structs.c			--- */
int		free_env(t_env *first);
int		free_all(t_min *tk, int out);
int		free_parser(t_parser *words, int out);
int		free_commands(t_cmd **first, int out);

#endif
