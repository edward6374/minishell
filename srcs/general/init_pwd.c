/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:30:46 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/29 15:44:13 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"

void init_pwd(t_min *tk)
{
	(void)tk;

	t_env *find;
	find = env_find(tk->env, "PWD", find_env);
	tk->pwd = ft_strdup(find->value);
	find = env_find(tk->env, "HOME", find_env);
	tk->home = ft_strdup(find->value);
	tk->oldpwd = NULL;
}
