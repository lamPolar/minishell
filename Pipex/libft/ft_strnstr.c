/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:41:18 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/01 20:37:39 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	bindex;
	size_t	lsize;

	bindex = 0;
	lsize = ft_strlen(little);
	if (lsize == 0)
		return ((char *)big);
	while (big[bindex] && bindex + lsize <= len)
	{
		if (ft_strncmp(big + bindex, little, lsize) == 0)
			return ((char *)(big + bindex));
		bindex++;
	}
	return (0);
}
