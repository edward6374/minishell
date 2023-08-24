/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:49:21 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/24 12:22:09 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "minishell.h"

int	ft_exit(t_cmd *temp) {
  int i;
  int value;

  i = -1;
  if (isatty(STDIN_FILENO))
    write(2, "exit\n", 6);
  if (!temp->args[1])
    exit(0);
  while (temp->args[1][++i]) {
    if (!ft_isdigit(temp->args[1][i])) {
      printf("minishell: exit: %s: number argument required\n", temp->args[1]);
      exit(255);
    }
  }
  if (temp->args[2]) {
    printf("minishell: exit: too many arguments\n");
    return (1);
  }
  value = ft_atoi(temp->args[1]);
  g_exit = value;
  exit(value);
  return (0);
}
