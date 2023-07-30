/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:51:33 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/29 18:57:42 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_pwd(t_cmd *temp, int p)
{
	int		i;
	char	path[256];

	if (getcwd(path, sizeof(path)) == NULL)
		exit(1);
	if (temp->out != 1)
		ft_putstr(fd, path, p);
	else
		printf("%s\n", path);
	return (0);
}
