/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:28:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/26 13:55:32 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count += 1;
	return (count);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*new;
	size_t			index;
	unsigned char	*ptr;

	new = (void *)ft_calloc(count, size);
	if (new == NULL)
	{
		printf("kinder: %s\n", strerror(errno));
		return (NULL);
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
		index += 1;
	}
	dst[dlen + index] = '\0';
	return (dlen + slen);
}

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	slen;

	slen = ft_strlen(s1);
	new = (char *)ft_calloc(sizeof(char), slen + 1);
	if (new == NULL)
		return (NULL);
	while (slen > 0)
	{	
		new[slen] = s1[slen];
		slen -= 1;
	}
	new[0] = s1[0];
	return (new);
}
