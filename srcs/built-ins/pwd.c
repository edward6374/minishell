/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:51:33 by vduchi            #+#    #+#             */
/*   Updated: 2023/07/22 15:52:30 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_pwd(void)
{
	char	path[256];

	if (getcwd(path, sizeof(path)) == NULL)
		exit(1);
	printf("%s\n", path);
	return (0);
}
