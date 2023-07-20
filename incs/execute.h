/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/16 14:00:04 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

//int		check_command(t_minishell *comands);

//void	minishell(t_minishell *tokens, char *env[], char *str);

/* ---		Run_command.c		--- */
//int		run_commands(t_minishell *tokens, char *env[]);

//int		pipes(t_minishell *tokens, char *env[]);
//char 	*ft_find_path(char *env[]);
//void	ft_printer(t_minishell *command, char **env);

/* ---			Execute_commands.c			--- */
int	execute_commands(t_minishell *tokens);

#endif
