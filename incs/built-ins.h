/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:45 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/23 18:12:29 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"

enum
{
	FALSE,
	TRUE
};

typedef struct s_quotes
{
	int		len;
	char	*tmp;
	int		i;
	int		j;

}			t_quotes;

// int			ft_cd(t_cmd *temp);
int			ft_cd(char **args, t_env *env);
int			ft_pwd(t_cmd *temp, int p);
int			ft_echo(char **args, int i);
int			ft_exit(t_cmd *temp);
int			ft_unset(t_min *tk, t_cmd *temp);
int			ft_env(t_min *tk, t_cmd *temp, int p);
int			ft_export(t_min *tk, t_cmd *temp, int p);

// Utils
int			find_env(char *s1, char *s2, int mode);
int			export_add(t_env *env, char **args);
void		env_add_back(t_env **env, t_env *new_node);
t_env		*new_env(char *str, char *value);
t_env		*env_find(t_env *env, void *data_ref, int (*cmp)(char *, char *,
					int));

#endif
