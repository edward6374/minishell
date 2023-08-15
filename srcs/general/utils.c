/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:57:06 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/14 21:02:29 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

void	siginthandler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	exit_error(const char *str, int i)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(i);
}

int	end_program(char **line, int error)
{
	if (line)
	{
		free(*line);
		*line = NULL;
	}
	if (error < 8)
		printf("%s\n", g_error_array[error - 1]);
	return (error);
}

int	d_key(t_min **tk)
{
	(void)tk;
	rl_clear_history();
	free_all(*tk, 0);
	return (0);
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
