/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:41:09 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/01 19:20:43 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;

	index = 0;
	while (index + 1 < dstsize && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	if (dstsize)
		dst[index] = '\0';
	return (ft_strlen(src));
}
