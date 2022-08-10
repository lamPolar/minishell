/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:12:35 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/06 17:50:25 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_positive(int n, int fd)
{
	char	mod;

	if (!n)
		return ;
	mod = n % 10 + '0';
	n /= 10;
	ft_put_positive(n, fd);
	write(fd, &mod, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	mod;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		mod = -(n % 10) + '0';
		n /= -10;
		ft_put_positive(n, fd);
		write(fd, &mod, 1);
	}
	else
		ft_put_positive(n, fd);
}
