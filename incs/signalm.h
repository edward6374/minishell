/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:54:55 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/23 22:35:02 by nmota-bu         ###   ########.fr       */
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
void	ign_signal(int signal);

#endif
