/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:46:49 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 20:27:50 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_with_argument(t_node *argument)
{
	int		check;

	if (check_equal(argument->str))
	{
		check = check_invalid(argument->str);
		if (check == 1)
		{
			print_error("KINDER: export: \'", argument->str, \
				"\': not a valid identifier", 0);
			return (1);
		}
		else if (check == 2)
			return (add_to_env_plus(argument->str, SHOW));
		return (add_to_env(argument->str, SHOW));
	}
	return (change_env_show(argument->str));
}

int	change_env_show(char *str)
{
	t_envp	*env;

	env = g_env;
	while (env)
	{
		if (ft_strequal(env->key, str))
		{
			env->display = SHOW;
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int	builtin_export(t_node *argument)
{
	t_envp	*env;
	t_envp	*free;

	env = sort_envp(get_env_size(g_env), -1);
	free = env;
	if (argument == NULL)
	{
		while (env)
		{
			if (env->display == SHOW)
				printf("declare -x %s = \"%s\"\n", env->key, env->value);
			env = env->next;
		}
		free_envp(free);
		return (0);
	}
	while (argument)
	{
		if (export_with_argument(argument))
			return (1);
		argument = argument->right;
	}
	free_envp(free);
	return (0);
}

t_envp	*sort_envp(int size, int i)
{
	t_envp	*res;
	char	**env;
	char	*temp;
	int		j;

	env = dearrange_envp();
	while (++i < size)
	{
		j = -1;
		while (++j < size - 1 - i)
		{
			if (env[j][0] > env[j + 1][0])
			{
				temp = ft_strdup(env[j]);
				free(env[j]);
				env[j] = ft_strdup(env[j + 1]);
				free(env[j + 1]);
				env[j + 1] = temp;
			}
		}
	}
	res = arrange_envp(env);
	free_double_array(env);
	return (res);
}
