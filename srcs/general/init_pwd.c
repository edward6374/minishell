/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:30:46 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/31 18:31:43 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "minishell.h"

void	init_pwd(t_min *tk)
{
	t_env	*find;

	find = env_find(tk->env, "PWD", find_env);
	tk->pwd = ft_strdup(find->value);
	find = env_find(tk->env, "HOME", find_env);
	tk->home = ft_strdup(find->value);
	tk->oldpwd = NULL;
}
