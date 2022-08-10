/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:41:06 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/01 16:45:15 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	index = 0;
	if (dlen > dstsize)
		return (dstsize + slen);
	while (dlen + index + 1 < dstsize && src[index])
	{
		dst[dlen + index] = src[index];
		index++;
	}
	dst[dlen + index] = '\0';
	return (dlen + slen);
}
