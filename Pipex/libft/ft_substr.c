/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:49:47 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/08 18:21:51 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;

	slen = ft_strlen(s);
	if (len > slen)
		new = (char *)ft_calloc(slen + 1, sizeof(char));
	else
		new = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (0);
	if (start <= (unsigned int)slen)
		ft_strlcpy(new, s + start, len + 1);
	return (new);
}
