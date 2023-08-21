/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:54:55 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/21 16:56:19 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALM_H
# define SIGNALM_H

enum
{
	NORMAL,
	INTERACT,
};

void	set_signals(int mode);

#endif
