/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:57:06 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/03 20:13:01 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	end_program(char **string, int error)
{
	free(*string);
	*string = NULL;
	if (error < 4)
		printf("%s\n", g_error_array[error]);
	return (0);
}

int	d_key(void)
{
	rl_clear_history();
//	ft_exit();
	return (1) ;
}

void	siginthandler(int sig)
{
	(void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
    rl_redisplay();
}

char	*ft_find_path(char *env[])
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}
