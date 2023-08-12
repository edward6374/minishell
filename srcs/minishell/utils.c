/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:57:06 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/12 06:42:41 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

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
//	free_all(&tk);
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

char	*get_curr_path(void)
{
	char	*path;
	char	get_path[256];

	getcwd(get_path, sizeof(get_path));
	path = ft_strjoin("\033[0;96m", get_path);
	path = ft_strjoin(path, "\033[0;0m > ");
	return (path);
}
