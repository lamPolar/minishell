/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:41:00 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/01 17:21:57 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	character;
	int		index;

	character = (char)c;
	index = 0;
	while (s[index])
	{
		if (s[index] == character)
			return ((char *)(s + index));
		index++;
	}
	if (s[index] == character)
		return ((char *)(s + index));
	return (0);
}
