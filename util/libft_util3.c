/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:51:03 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/31 15:18:11 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	free_both(char *s1, char *s2)
{
	if (s1)
		free(s1);
	s1 = NULL;
	if (s2)
		free(s2);
	s2 = NULL;
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
	int	i;

	if ((str[0] < 'A' || str[0] > 'z') && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] < 'A' || str[i] > 'z') && str[i] != '_' \
			&& (str[i] < '0' || str[i] > '9'))
		{
			if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
				return (2);
			return (1);
		}
		i += 1;
	}
	return (0);
}

int	max(int len1, int len2)
{
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}
