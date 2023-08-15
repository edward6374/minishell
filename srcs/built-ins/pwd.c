/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:51:33 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/15 20:02:47 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_pwd(t_cmd *tmp, int p)
{
	char	*pwd;

	pwd = getcwd(NULL, sizeof(char *));
	if (tmp->next)
	{
		ft_putstr_fd(pwd, p);
		ft_putchar_fd('\n', p);
	}
	else
		printf("%s\n", pwd);
	free(pwd);
	return (0);
}
