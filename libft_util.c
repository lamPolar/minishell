/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:28:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/24 18:07:55 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*new;
	size_t			index;
	unsigned char	*ptr;

	new = (void *)malloc(count * size);
	if (!new)
	{
		printf("kinder: %s\n", strerror(errno));
		return (0);
	}
	index = 0;
	ptr = (unsigned char *)new;
	while (index < count * size)
	{	
		ptr[index] = '\0';
		index += 1;
	}
	return (new);
}

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