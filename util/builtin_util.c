/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:32:02 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 01:04:26 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	change_env_value(char *str, int display, t_envp	*env)
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

int	change_env_value_plus(char *str, int display, t_envp *env)
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

int	add_to_env(char *str, int display)
{
	t_envp	*prev;
	t_envp	*env;
	char	*key;

	env = g_env;
	prev = env;
	key = envp_split_key(str);
	if (key == NULL)
		return (1);
	while (env)
	{
		if (ft_strequal(env->key, key))
		{	
			free(key);
			return (change_env_value(str, display, env));
		}
		prev = env;
		env = env->next;
	}
	free(key);
	return (append_envp(env, prev, str, display));
}

int	add_to_env_plus(char *str, int display)
{
	t_envp	*prev;
	t_envp	*env;
	char	*key;

	env = g_env;
	prev = env;
	key = envp_split_key(str);
	if (key == NULL)
		return (1);
	while (env)
	{
		if (ft_strequal(env->key, key))
		{
			free(key);
			return (change_env_value_plus(str, display, env));
		}
		prev = env;
		env = env->next;
	}
	free(key);
	return (append_envp(env, prev, str, display));
}

int	append_envp(t_envp *env, t_envp *prev, char *str, int display)
{
	t_envp	*new;

	if (env == NULL)
	{
		new = make_new_envp(str, display);
		if (new == NULL)
			return (1);
		prev->next = new;
	}
	return (0);
}
