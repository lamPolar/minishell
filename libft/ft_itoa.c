/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 15:29:57 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/06 17:26:43 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_length(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count += 2;
		n /= -10;
	}
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_ten(char *new, int n, int len)
{
	if (n == 0)
	{
		new[0] = '0';
		return ;
	}
	if (n < 0)
	{
		new[0] = '-';
		new[len--] = -(n % 10) + '0';
		n /= -10;
	}
	while (n)
	{
		new[len--] = n % 10 + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*new;
	int		len;

	len = ft_count_length(n);
	new = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (0);
	ft_ten(new, n, --len);
	return (new);
}
