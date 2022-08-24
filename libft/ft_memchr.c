/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:40:46 by heeskim           #+#    #+#             */
/*   Updated: 2021/11/30 17:45:36 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	character;
	size_t			index;

	ptr = (unsigned char *)s;
	character = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (ptr[index] == character)
			return ((void *)(s + index));
		index++;
	}
	return (0);
}
