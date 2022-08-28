/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:48:05 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 15:32:40 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_env_value(char *key, t_envp *env)
{
	char	*value;

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

static void	delete_env(char *str, t_envp **head)
{
	int		len1;
	int		len2;
	t_envp	*env;
	t_envp	*prev;

	len1 = ft_strlen(str);
	env = *head;
	while (env)
	{
		len2 = ft_strlen(env->key);
		if (ft_strequal(str, env->key))
		{
			if (prev == env)
				*head = env->next;
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

int	builtin_unset(t_node *command, t_envp *env)
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
				printf("KINDER: unset: %s: not a valid identifier", \
						argument->str);
				return (1);
			}
			delete_env(argument->str, &env);
			argument = argument->right;
		}
	}
	return (0);
}

int	builtin_env(t_envp *env)
{
	while (env)
	{
		if (env->display == SHOW)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);//error로 삽입
}
