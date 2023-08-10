/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:57:06 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/10 11:22:09 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	exit_error(const char *str, int i)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(i);
}

int	end_program(char **string, int error)
{
	if (string)
	{
		free(*string);
		*string = NULL;
	}
	if (error < 8)
		printf("%s\n", g_error_array[error - 1]);
	return (error);
}

int	d_key(void)
{
	rl_clear_history();
	//	ft_exit();
	return (1);
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
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}
