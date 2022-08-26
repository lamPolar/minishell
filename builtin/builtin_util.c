/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:32:02 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/26 16:03:35 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_strequal(char *s1, char *s2)
{
	int	i;
	int	len1;
	int	len2;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (0);
	while (i < len1)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_invalid(char *str)
{
	if ((str[0] < 'A' || str[0] > 'z') && str[0] != '_')
		return (1);
	return (0);
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || str[i] != '+' || str[i] != '-' \
			|| str[i] < 9 || str[i] > 13 || str[i] != 32)
			return (0);
		i += 1;
	}
	return (1);
}

int	max(int len1, int len2)
{
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}
