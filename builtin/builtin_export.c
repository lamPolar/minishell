/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:46:49 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/27 22:26:38 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	change_env_value(char *str, t_envp *env)
{
	char	*value;

	value = envp_split_val(str);
	if (value == NULL)
		return (1);
	free(env->value);
	env->value = value;
	env->display = SHOW;
	return (0);
}

int	add_to_env(char *str, t_envp *env)
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
			return (change_env_value(str, env));
		}
		prev = env;
		env = env->next;
	}
	free(key);
	if (env == NULL)
	{
		new = make_new_envp(str);
		if (new == NULL)
			return (1);
		prev->next = new;
	}
	return (0);
}

int	export_with_argument(t_node *argument, t_envp *env)
{
	if (check_equal(argument->str))
	{
		if (check_invalid(argument->str))
		{
			printf("KINDER: export: \'%s\': not a valid identifier\n", \
			argument->str);
			return (1);
		}
		return (add_to_env(argument->str, env));
	}
	while (env)
	{
		if (ft_strequal(env->key, argument->str))
		{
			env->display = SHOW;
			return (0);
		}
		env = env->next;
	}
}

int	builtin_export(t_node *command, t_envp *env)
{
	t_envp	*new;
	t_node	*argument;

	argument = command->right;
	if (argument == NULL)
	{
		//env 오름차순 sorting??
		while (env)
		{
			if (env->display == SHOW)
				printf("declare -x %s = \"%s\"\n", env->key, env->value);
			env = env->next;
		}
		if (env == NULL)
			return (0);
		return (1);
	}
	else
	{
		while (argument)
		{
			if (export_with_argument(argument, env))
				return (1);
			argument = argument->right;
		}
		if (argument == NULL)
			return (0);
		return (1);
	}
}

//만약 파이프 뒤에 export를 호출하면, 자식프로세스에 대한 export이므로 환경변수에 대해서 변경하지 않음

//export TE\ST=100 ok
//export TE\\ST=100 x
//export TES\\\ST=100 x
//export TEST+=100 -> 원래 TEST환경변수의 value뒤에 추가되어야함.

// 환경변수 key한글자 한글자에 대해서 모두 valid체크 해줘야할까?
//export 에서 에러가 나면 exit해버릴까???
