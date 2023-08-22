/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:54:55 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/22 12:39:05 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALM_H
# define SIGNALM_H

enum
{
	NORMAL,
	INTERACT,
	HEREDOC,
};

void	set_signals(int mode);

#endif
