/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:41:04 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/01 19:06:12 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	slen;

	slen = ft_strlen(s1);
	new = (char *)malloc(sizeof(char) * (slen + 1));
	if (!new)
		return (0);
	while (slen > 0)
	{	
		new[slen] = s1[slen];
		slen--;
	}
	new[0] = s1[0];
	return (new);
}
