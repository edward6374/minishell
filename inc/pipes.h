/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:18:34 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/03 18:44:56 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_command
{
	int					ok;;
	int					in;
	int					out;
	char				*cmd;
	char				**args;
	struct s_command	*next;
}	t_command;

typedef struct s_minishell
{
	char		**path;
	t_command	*command;
}	t_minishell;

int		check_command(t_minishell *comands);

/* ---		Run_command.c		--- */
int		run_commands(t_command *token, char *env[]);

int		pipes(t_minishell *tokens, char *env[]);
//char 	*ft_find_path(char *env[]);
void	ft_printer(t_minishell *command, char **env);

#endif
