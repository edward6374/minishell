/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/16 18:26:24 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/* ---			Execute_commands.c			--- */
int		execute_commands(t_min *tk);

/* ---			Utils.c				--- */
int		is_builtin(t_min *tk, t_cmd *tmp, int p);
char	**take_double(t_env *first);
void 	end_exec(t_min *tk, pid_t *child_pid, char **env);

/* ---			Pipes_and_hdoc			--- */
void	run_here_doc(t_cmd *tmp);
void	close_here_doc(t_min *tk);
void	close_all_pipes(t_min *tk, int *p, int fd);
void	check_temp_fd(t_cmd *tmp, int *p, int *fd);
void	redirect_pipes(t_cmd *tmp, int *p, int fd);


#endif
