/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:58:53 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/06 17:54:53 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_stpcpy(char *dst, const char *src, size_t len)
{
	size_t	index;

	index = 0;
	while (index + 1 < len && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (dst + index);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new)
		return (0);
	ft_strlcpy(ft_stpcpy(new, s1, len1 + 1), s2, len2 + 1);
	return (new);
}
