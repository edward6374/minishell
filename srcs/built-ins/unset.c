/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:01 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/26 19:29:24 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

void	change_var(t_env *loop, int *i)
{
	t_env *next;

	next = loop->next;
	loop->before->next = loop->next;
	loop->next->before = loop->before;
	free(loop->str);
	free(loop);
	loop = next;
	*i = -1;
}

int	ft_unset(t_min *tk, t_cmd *temp)
{
	int		i;
	int		len;
	t_env	*loop;

	printf("Unset\n");
	loop = tk->env;
	if (!temp->args[1])
		return (0);
	while (loop)
	{
		i = -1;
		while (temp->args[++i])
		{
			if (!ft_strrchr(loop->str, '='))
				len = (int)ft_strlen(loop->str);
			else
				len = ft_strrchr(loop->str, '=') - loop->str + 1;
			if (!ft_strncmp(temp->args[i], loop->str, len))
				change_var(loop, &i);
		}
		loop = loop->next;
	}
	return (0);
}
