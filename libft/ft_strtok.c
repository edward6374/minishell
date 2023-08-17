/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmota-bu <nmota-bu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:11:42 by nmota-bu          #+#    #+#             */
/*   Updated: 2023/08/17 22:20:23 by nmota-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	char		*token_start;
	static char	*next_token;
	char		*token_end;

	if (str != NULL)
		next_token = str;
	else if (next_token == NULL)
		return (NULL);
	token_start = next_token;
	token_end = ft_strpbrk(token_start, delim);
	if (token_end != NULL)
	{
		*token_end = '\0';
		next_token = token_end + 1;
	}
	else
		next_token = NULL;
	return (token_start);
}
