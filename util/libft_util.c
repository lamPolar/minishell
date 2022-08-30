/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:28:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 00:49:50 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	ft_strlen(const char *s)
{
	int	count;

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

	new = (void *)malloc(count * size);
	if (new == NULL)
	{
		print_error("KINDER: ", strerror(errno), 0, 0);
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

int	ft_strequal(char *s1, char *s2)
{
	int	i;
	int	len1;
	int	len2;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (0);
	while (i < len1)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
