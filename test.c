/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:00:14 by vduchi            #+#    #+#             */
/*   Updated: 2023/06/04 18:05:34 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int main(int argc, char **argv, char *env[])
{
	char	*str = "/bin/cat";
	char	**args;

	args = malloc(sizeof(char *) * 4);
	args[0] = ft_strdup("cat");
	args[1] = ft_strdup("<test.txt");
	args[2] = ft_strdup("<test.txt");
	args[3] = NULL;
	execve(str, args, env);
}
