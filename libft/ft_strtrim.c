/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:05:24 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/06 20:09:46 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	index;
	size_t	len;
	char	*new;

	index = 0;
	len = ft_strlen(s1);
	while (s1[index] && ft_strchr(set, s1[index]))
		index++;
	if (index == len)
		return (ft_strdup(""));
	len--;
	while (s1[len] && ft_strchr(set, s1[len]))
		len--;
	new = (char *)ft_calloc(len - index + 2, sizeof(char));
	if (!new)
		return (0);
	ft_strlcpy(new, s1 + index, len - index + 2);
	return (new);
}
