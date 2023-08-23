/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:57:06 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/23 23:11:34 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

void	set_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	exit_error(const char *str, int i)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(i);
	return (1);
}

int	end_program(char **line, int error)
{
	if (line)
	{
		free(*line);
		*line = NULL;
	}
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
