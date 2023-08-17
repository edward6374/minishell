/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:12:56 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/17 22:19:29 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *str, const char *charset)
{
	const char	*char_ptr;

	while (*str != '\0')
	{
		char_ptr = charset;
		while (*char_ptr != '\0')
		{
			if (*char_ptr == *str)
				return ((char *)str);
			char_ptr++;
		}
		str++;
	}
	return (NULL);
}
