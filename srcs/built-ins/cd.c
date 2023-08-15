/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:25:00 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/15 21:04:58 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	change_directory(const char *path)
{
	if (chdir(path) == 0)
		return (0); // Cambio de directorio exitoso
	else
	{
		perror("cd"); // Imprime un mensaje de error similar a Bash
		return (-1);  // Cambio de directorio fallido
	}
}

int	ft_cd(t_cmd *tmp)
{
	change_directory(tmp->args[1]);
	return (0);
}

// if (chdir(temp->args[0]) == -1)
// 	return (PATH_ERROR);
