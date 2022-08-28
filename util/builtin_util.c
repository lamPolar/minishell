/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:32:02 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 15:29:58 by heeskim          ###   ########.fr       */
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

int	change_env_value(char *str, t_envp *env, int display)
{
	char	*save;
	char	*value;

	value = envp_split_val(str);
	if (value == NULL)
		return (1);
	save = env->value;
	env->value = value;
	free(save);
	env->display = display;
	return (0);
}

int	add_to_env(char *str, t_envp *env, int display)
{
	t_envp	*new;
	t_envp	*prev;
	char	*key;

	key = envp_split_key(str);
	if (key == NULL)
		return (1);
	while (env)
	{
		if (ft_strequal(env->key, key))
		{	
			free(key);
			return (change_env_value(str, env, display));
		}
		prev = env;
		env = env->next;
	}
	free(key);
	if (env == NULL)
	{
		new = make_new_envp(str, display);
		if (new == NULL)
			return (1);
		prev->next = new;
	}
	return (0);
}

int	change_env_value_plus(char *str, t_envp *env, int display)
{
	char	*value;

	value = envp_split_val(str);
	if (value == NULL)
		return (1);
	value = ft_strjoin(env->value, value, 0);
	if (value == NULL)
		return (1);
	free(env->value);
	env->value = value;
	env->display = display;
	return (0);
}

int	add_to_env_plus(char *str, t_envp *env, int display)
{
	t_envp	*new;
	t_envp	*prev;
	char	*key;

	key = envp_split_key(str);
	if (key == NULL)
		return (1);
	while (env)
	{
		if (ft_strequal(env->key, key))
		{
			free(key);
			return (change_env_value_plus(str, env, display));
		}
		prev = env;
		env = env->next;
	}
	free(key);
	if (env == NULL)
	{
		new = make_new_envp(str, display);
		if (new == NULL)
			return (1);
		prev->next = new;
	}
	return (0);
}