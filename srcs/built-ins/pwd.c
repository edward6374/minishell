/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:51:33 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/23 10:02:39 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_pwd(t_cmd *tmp, int p)
{
	char	*pwd;

	(void)p;
	(void)tmp;
	pwd = getcwd(NULL, sizeof(char *));
	// if (tmp->next)
	// {
	// ft_putstr_fd(pwd, p);
	// ft_putchar_fd('\n', p);
	// }
	// else
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
