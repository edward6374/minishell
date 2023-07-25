/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/25 20:11:56 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

//int		check_command(t_min *comands);

//void	minishell(t_min *tk, char *env[], char *str);

/* ---		Run_command.c		--- */
//int		run_commands(t_min *tk, char *env[]);

//int		pipes(t_min *tk, char *env[]);
//char 	*ft_find_path(char *env[]);
//void	ft_printer(t_min *command, char **env);

/* ---			Execute_commands.c			--- */
int	execute_commands(t_min *tk);

#endif
