/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:50:19 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/22 12:39:09 by vduchi           ###   ########.fr       */
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
		g_exit = 1;
	}
}

void	interact_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_exit = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_exit = 131;
	}
}

void	set_signals(int mode)
{
	struct sigaction	signal;

	// printf("Signals\n");
	signal.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	if (mode == NORMAL)
		signal.sa_handler = norm_handler;
	else if (mode == INTERACT)
		signal.sa_handler = interact_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	if (mode == NORMAL)
	{
		signal.sa_handler = SIG_IGN;
		sigemptyset(&signal.sa_mask);
		sigaction(SIGQUIT, &signal, NULL);
	}
}
