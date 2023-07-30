/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:45 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/29 19:40:42 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"

int		ft_cd(t_cmd *temp);
int		ft_pwd(t_cmd *temp, int p);
int		ft_echo(t_cmd *temp, int p);
int		ft_exit(t_min *tk, t_cmd *temp);
int		ft_unset(t_min *tk, t_cmd *temp);
int		ft_env(t_min *tk, t_cmd *temp, int p);
int		ft_export(t_min *tk, t_cmd *temp, int p);

#endif
