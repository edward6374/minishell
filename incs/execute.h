/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/30 10:32:27 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_run
{
	int		status;
	pid_t	pid;
	char	*l;
}			t_run;

/* ---			Execute_commands.c			--- */
int			execute_commands(t_min *tk);
int			check_before_exec(t_min *tk, t_cmd **tmp, int *p, int *fd);
void		take_exit_value(t_cmd *tmp);

/* ---			Utils.c				--- */
int			run_builtin(t_min *tk, t_cmd *tmp);
char		**take_double(t_min *tk, t_env *first);
void		one_builtin(t_min *tk, t_cmd *tmp, pid_t *child_pid);
void		set_g(t_min *tk, int ok);
void		end_exec(t_min *tk, pid_t *child_pid, char **env);
void		take_more_exit(char **str, int i);

/* ---			Pipes_and_hdoc			--- */
int			is_builtin(char *cmd);
void		close_all_pipes(t_min *tk, int *p, int fd);
void		check_temp_fd(t_cmd *tmp, int *p, int *fd);
void		redirect_pipes(t_cmd *tmp, int *p, int fd);

/* ---			Run_here_doc			--- */
void		run_here_doc(t_cmd *tmp);
void		close_here_doc(t_min *tk);

#endif
