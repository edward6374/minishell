/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/23 10:11:41 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/* ---			Execute_commands.c			--- */
int		execute_commands(t_min *tk);
void take_exit_value(t_cmd *tmp);

/* ---			Utils.c				--- */
int is_builtin(char *cmd);
int run_builtin(t_min *tk, t_cmd *tmp, int p);
char **take_double(t_min *tk, t_env *first);
void set_g(t_min *tk, int ok);
void 	end_exec(t_min *tk, pid_t *child_pid, char **env);

/* ---			Pipes_and_hdoc			--- */
void	run_here_doc(t_cmd *tmp);
void	close_here_doc(t_min *tk);
void	close_all_pipes(t_min *tk, int *p, int fd);
void	check_temp_fd(t_cmd *tmp, int *p, int *fd);
void	redirect_pipes(t_cmd *tmp, int *p, int fd);

#endif
