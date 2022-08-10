/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:40:55 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/01 20:30:59 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			index;
	unsigned char	*d;
	unsigned char	*s;

	if (dst == src || len == 0)
		return (dst);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	index = 0;
	if (dst < src)
	{
		while (index < len)
		{
			d[index] = s[index];
			index++;
		}
		return (dst);
	}
	while (index < len)
	{
		d[len - index - 1] = s[len - index - 1];
		index++;
	}
	return (dst);
}
