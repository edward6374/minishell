/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:57:06 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/21 13:33:07 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

//void	siginthandler(int sig)
//{
//	if (sig == SIGINT)
//	{
//		write(1, "\n", 1);
//		rl_replace_line("", 0);
//		rl_on_new_line();
//		rl_redisplay();
//	}
//	else if (sig == SIGQUIT)
//	{
//		ft_putstr_fd("Quit: 3\n", 2);
//		exit (131);
//	}
//	ft_putstr_fd("Sig handler\n", 2);
////	printf("Sighandler: %d\n", sig);
//}

void	norm_handler(int sig, siginfo_t *data, void *tk)
{
	t_min	*tmp;

	(void) data;
	tmp = (t_min *)tk;
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		tmp->exit_value = 1;
	}
}

void	interact_handler(int sig, siginfo_t *data, void *tk)
{
	t_min	*tmp;

	(void) data;
	tmp = (t_min *)tk;
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		tmp->exit_value = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		tmp->exit_value = 131;
	}
}

void	set_signals(t_min *tk, int mode)
{
	struct sigaction	signal;

	signal.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	if (mode == NORMAL)
		signal.sa_sigaction = norm_handler;
	else if (mode == INTERACT)
		signal.sa_sigaction = interact_handler;
	signal.sa_userdata = tk;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
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
