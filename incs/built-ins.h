/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:45 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/14 21:16:28 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"

typedef struct s_quotes
{
	int		len;
	char	*tmp;
	int		i;
	int		j;

}			t_qoutes;

int			ft_cd(t_cmd *temp);
int			ft_pwd(t_cmd *temp, int p);
int			ft_echo(t_cmd *temp, int p);
int			ft_exit(t_min *tk, t_cmd *temp);
int			ft_unset(t_min *tk, t_cmd *temp);
int			ft_env(t_min *tk, t_cmd *temp, int p);
int			ft_export(t_min *tk, t_cmd *temp, int p);

// Utils
char		**take_double(t_env *first);
void		export_add(t_env *env, char **args);

#endif
