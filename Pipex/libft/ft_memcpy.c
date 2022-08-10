/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:40:52 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/01 20:30:58 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*d;
	unsigned char	*s;

	if (dst == src || n == 0)
		return (dst);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	index = 0;
	while (index < n)
	{
		d[index] = s[index];
		index++;
	}
	return (dst);
}
