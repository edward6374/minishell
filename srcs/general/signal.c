/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:50:19 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/21 16:58:30 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "signalm.h"
#include <signal.h>

void	norm_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		// tmp->exit_value = 1;
		g_exit = 1;
	}
}

void	interact_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		// tmp->exit_value = 130;
		g_exit = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		// tmp->exit_value = 131;
		g_exit = 131;
	}
}

void	set_signals(int mode)
{
	struct sigaction	signal;

	printf("Signals\n");
	signal.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	if (mode == NORMAL)
		signal.sa_handler = norm_handler;
	else if (mode == INTERACT)
		signal.sa_handler = interact_handler;
	// signal.sa_sigaction(SIGINT, NULL, tk);
	// signal.sa_sigaction(SIGQUIT, NULL, tk);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}
