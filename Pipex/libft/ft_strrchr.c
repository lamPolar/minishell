/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:41:21 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/01 20:00:39 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	character;
	size_t	slen;

	slen = ft_strlen(s);
	character = (char)c;
	while (slen > 0)
	{
		if (s[slen] == character)
			return ((char *)(s + slen));
		slen--;
	}
	if (s[0] == character)
		return ((char *)(s));
	return (0);
}
