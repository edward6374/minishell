/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:50:19 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/23 16:47:51 by vduchi           ###   ########.fr       */
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
		// write(1, "Norm INT\n", 9);
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 1;
	}
	return ;
}

void	interact_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		// write(1, "Inter INT\n", 10);
		g_exit = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		// write(1, "Inter QUIT\n", 11);
		g_exit = 131;
	}
	return ;
}

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_exit = 130;
		exit(130);
	}
	return ;
}
/*
void	set_signals(int mode)
{
	struct sigaction	signal;

	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (mode == NORMAL)
		signal.sa_handler = norm_handler;
	else if (mode == INTERACT)
		signal.sa_handler = interact_handler;
	else if (mode == HEREDOC)
		signal.sa_handler = heredoc_handler;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}

void ign_signal(int signal)
{
	struct sigaction sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(signal, &sa, NULL);
}
*/
void ign_signal(int signal)
{
	struct sigaction sa;

	sa.sa_handler = SIG_IGN;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signal, &sa, NULL) < 0)
		exit(1);
}

void set_signals(int mode)
{
	struct sigaction sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (mode == 0)
		sa.sa_handler = &norm_handler;
	else if (mode == 1)
		sa.sa_handler = &interact_handler;
	else if (mode == 2)
		sa.sa_handler = &heredoc_handler;
	else if (mode == 3)
		sa.sa_handler = &ign_signal;
	sigaction(SIGINT, &sa, NULL);
	if (!mode)
	{
		sa.sa_handler = SIG_IGN;
		sa.sa_flags = SA_RESTART;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGQUIT, &sa, NULL);
	}
	sigaction(SIGQUIT, &sa, NULL);
}
