/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:48:19 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/31 00:49:16 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

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

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+' && str[i] != '-' \
			&& (str[i] < 9 || str[i] > 13) && str[i] != 32)
			return (0);
		i += 1;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	result;
	long long	tmp;
	long long	sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tmp = result;
		result = result * 10 + (*str - '0');
		if (tmp > result && sign < 0)
			return (0);
		if (tmp > result && sign > 0)
			return (-1);
		str++;
	}
	return ((int)(result * sign));
}
