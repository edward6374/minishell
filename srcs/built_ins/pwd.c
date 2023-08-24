/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:51:33 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/24 11:55:03 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, sizeof(char *));
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
