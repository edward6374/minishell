/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:54:55 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/23 10:39:37 by vduchi           ###   ########.fr       */
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
void ign_signal(int signal);

#endif
