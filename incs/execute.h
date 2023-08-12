/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/12 13:28:44 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/* ---			Execute_commands.c			--- */
int		execute_commands(t_min *tk);

/* ---			Utils.c				--- */
char	**take_double(t_env *first);
int		is_builtin(t_min *tk, t_cmd *tmp, int p);
void 	end_exec(t_min *tk, pid_t *child_pid, char **env);

#endif
