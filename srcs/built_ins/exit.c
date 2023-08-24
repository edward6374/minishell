/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:49:21 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/24 15:40:32 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "minishell.h"

void	exit_err_arg(char *str, long long int *value, int mode)
{
	if (!mode)
	{
		printf(":( exit: %s: number argument required\n", str);
		exit(255);
	}
	printf(":( exit: too many arguments\n");
	g_exit = 0;
	*value = 0;
}

int	check_only_numbers(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			break ;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	ft_exit(t_cmd *cmd)
{
	long long int	value;

	value = 0;
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
	if (!cmd->args[1])
		exit(0);
	else if ((!cmd->args[2] && !ft_strncmp(cmd->args[1], "", 1)))
		exit_err_arg(cmd->args[1], &value, 0);
	value = ft_atol(cmd->args[1]);
	if (value == 0 && ft_strncmp(cmd->args[1], "0", 2)
		&& ft_strncmp(cmd->args[1], "-0", 3) && ft_strncmp(cmd->args[1], "+0",
			3))
		exit_err_arg(cmd->args[1], &value, 0);
	else if (cmd->args[2])
		exit_err_arg(cmd->args[1], &value, 1);
	else
		exit(value);
	return (0);
}
