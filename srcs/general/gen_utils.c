/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:57:06 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/21 16:56:43 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

// void	norm_handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ft_putchar_fd('\n', 1);
// 		rl_replace_line("", 1);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		// tmp->exit_value = 1;
// 		g_exit = 1;
// 	}
// }

// void	interact_handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ft_putchar_fd('\n', 1);
// 		// tmp->exit_value = 130;
// 		g_exit = 130;
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 		ft_putstr_fd("Quit: 3\n", 1);
// 		// tmp->exit_value = 131;
// 		g_exit = 131;
// 	}
// }

// TODO
// arreglar senales
// void	set_signals(int mode)
// {
// 	struct sigaction	signal;

// 	printf("Signals\n");
// 	signal.sa_flags = SA_RESTART | SA_SIGINFO;
// 	sigemptyset(&signal.sa_mask);
// 	if (mode == NORMAL)
// 		signal.sa_handler = norm_handler;
// 	else if (mode == INTERACT)
// 		signal.sa_handler = interact_handler;
// 	// signal.sa_sigaction(SIGINT, NULL, tk);
// 	// signal.sa_sigaction(SIGQUIT, NULL, tk);
// 	sigaction(SIGINT, &signal, NULL);
// 	sigaction(SIGQUIT, &signal, NULL);
// }

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
