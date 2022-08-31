/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:48:05 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 02:41:59 by sojoo            ###   ########.fr       */
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
		print_error("KINDER: cd: ", key, " not set", 0);
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
		return (1);
	else
	{
		while (argument != NULL)
		{
			if (check_invalid(argument->str))
			{
				print_error("KINDER: unset: \'", argument->str, \
					"\': not a valid identifier", 0);
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
	return (0);
}
