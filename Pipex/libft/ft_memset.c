/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:40:57 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/01 17:21:35 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			index;
	unsigned char	*ptr;
	unsigned char	character;

	index = 0;
	ptr = (unsigned char *)b;
	character = (unsigned char)c;
	while (index < len)
	{
		ptr[index] = character;
		index++;
	}
	return (b);
}
