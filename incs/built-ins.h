/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:45 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/25 20:24:28 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"

int		ft_pwd(void);
int		ft_cd(t_cmd *temp);
int		ft_echo(t_cmd *temp);
int		ft_env(t_min *tk, t_cmd *temp);
int		ft_exit(t_min *tk, t_cmd *temp);
int		ft_unset(t_min *tk, t_cmd *temp);
int		ft_export(t_min *tk, t_cmd *temp);

char	**free_double_pointer(char **arr, int i);

#endif
