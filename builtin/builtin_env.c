/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:48:05 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/30 18:19:55 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_env_value(char *key)
{
	char	*value;
	t_envp	*env;

	env = g_env;
	while (env && ft_strequal(env->key, key) == 0)
		env = env->next;
	if (env == NULL)
	{
		printf("KINDER: cd: %s not set\n", key);
		return (NULL);
	}
	value = ft_strdup(env->value);
	return (value);
}

static void	delete_env(char *str)
{
	t_envp	*env;
	t_envp	*prev;

	env = g_env;
	while (env)
	{
		if (ft_strequal(str, env->key))
		{
			if (env == g_env)
				g_env = env->next;
			else
				prev->next = env->next;
			free(env->key);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

int	builtin_unset(t_node *command)
{
	t_node	*argument;

	argument = command->right;
	if (argument == NULL)
	{
		printf("USAGE: unset [KEY]\n");
		return (1);
	}
	else
	{
		while (argument != NULL)
		{
			if (check_invalid(argument->str))
			{
				printf("KINDER: unset: %s: not a valid identifier\n", \
						argument->str);
				return (1);
			}
			delete_env(argument->str);
			argument = argument->right;
		}
	}
	return (0);
}

int	builtin_env(void)
{
	t_envp	*env;

	env = g_env;
	while (env)
	{
		if (env->display == SHOW)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);//error로 삽입
}
