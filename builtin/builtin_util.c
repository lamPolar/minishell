/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:32:02 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/27 15:15:01 by heeskim          ###   ########.fr       */
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
	int i;

	if ((str[0] < 'A' || str[0] > 'z') && str[0] != '_')
		return (1);
	i = 1;
	while (str[i])
	{
		if ((str[i] < 'A' || str[i] > 'z') && str[i] != '_' && (str[i] < '0' || str[i] > '9'))
			return (1);
		i += 1;
	}
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

static char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	slen;

	slen = ft_strlen(s1);
	new = (char *)ft_calloc(sizeof(char), slen + 1);
	if (new == NULL)
		return (NULL);
	while (slen > 0)
	{	
		new[slen] = s1[slen];
		slen -= 1;
	}
	new[0] = s1[0];
	return (new);
}

char	*get_home(t_envp *env)
{
	char	*value_array;

	while (env && ft_strequal(env->key, "HOME") == 0)
		env = env->next;
	if (env == NULL)
		return (NULL);
		// 일단 아무거나 써둠
		//매치되는 환경변수 없으면? 어떻게 할까? 
		//-> command not found?
		//HOME not set?
	else
	{
		value_array = ft_strdup(env->value);
		if (value_array == NULL)
			return (NULL);
		return (value_array);
	} // 사실상 value_array 를 그대로 리턴하는거니까 널가드 필요 없음..?
}