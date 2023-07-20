/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:45 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/15 14:09:22 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"

int		ft_cd(char *path);
int		ft_exit(int value);
int		ft_echo(char *str);
int		ft_env(char *env[]);
char	**ft_unset(char *env[], char *str);
char	**ft_export(char *env[], char *new_string);

char	**free_double_pointer(char **arr, int i);

#endif
