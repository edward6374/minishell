/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:33:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/08/18 02:07:21 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newl)
{
	t_list	*my;

	my = NULL;
	if (!lst || !newl)
		return ;
	if (*lst == NULL)
		*lst = newl;
	else
	{
		my = *lst;
		while (my->next != NULL)
			my = my->next;
		my->next = newl;
	}
}
