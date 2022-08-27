/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:46:49 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 03:25:36 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
		return (add_to_env(argument->str, env, SHOW));
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

	//t_node	*argument;
	//argument = command->right;
int	builtin_export(t_node *argument, t_envp *env)
{
	t_envp	*new;

	//env 오름차순 sorting??
	if (argument == NULL)
	{
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

//만약 파이프 뒤에 export를 호출하면, 자식프로세스에 대한 export이므로 환경변수에 대해서 변경하지 않음

//export TE\ST=100 ok
//export TE\\ST=100 x
//export TES\\\ST=100 x
//export TEST+=100 -> 원래 TEST환경변수의 value뒤에 추가되어야함.

//export 에서 에러가 나면 exit해버릴까???
