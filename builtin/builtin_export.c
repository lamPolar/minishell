/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:46:49 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 15:33:32 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_with_argument(t_node *argument, t_envp *env)
{
	int	check;

	if (check_equal(argument->str))
	{
		check = check_invalid(argument->str);
		if (check == 1)
		{
			printf("KINDER: export: \'%s\': not a valid identifier\n", \
			argument->str);
			return (1);
		}
		else if (check == 2)
			return (add_to_env_plus(argument->str, env, SHOW));
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
	return (0); // error로 인한 삽입
}

	//t_node	*argument;
	//argument = command->right;
int	builtin_export(t_node *argument, t_envp *env)
{
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
//export 에서 에러가 나면 exit해버릴까???
