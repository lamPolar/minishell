/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:31:56 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/26 23:18:45 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_cd(t_node *command, t_envp *env)
{
	char	*home;

	if (command->right == NULL || ft_strequal(command->right->str, "~"))
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			printf("kinder: cd: HOME not set\n");
			return (1);
		}
		if (chdir(home) == -1)
		{
			printf("cd: HOME: %s\n", strerror(errno));
			return (1);
		}
	}
	else
	{
		if (chdir(command->right->str) == -1)
		{
			printf("cd: %s: %s\n", command->right->str, strerror(errno));
			return (1);
		}
	}
	return (0);
}

int	builtin_pwd(t_node *command)
{
	char	*buf;
	size_t	size;

	buf = NULL;
	buf = getcwd(buf, size);
	if (buf == NULL)
	{
		printf("KINDER: pwd: %s", strerror(errno));
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

int	builtin_exit(t_node *command, t_envp *env)
{
	t_node	*argument;

	if (command->right == NULL)
		exit(EXIT_SUCCESS);
	else
	{
		argument = command->right;
		if (argument->right == NULL)
		{
			if (ft_isnum(argument->str))
				exit(ft_atoi(argument->str));
			else
			{
				printf("exit\nkinder: exit: %s: numeric argument required", \
						argument->str);
				free_envp(env);
				//free_tree(head);
				exit(255);
			}
		}
		else
			printf("exit\nkinder: exit: too many arguments\n");
	}
}
	//free필요???
	/*
	exit만 입력시 -> exit출력 후 exit_success를 넘기면서 종료
	exit뒤에 인자가 있으면, 부모에게 상태값으로 전달 -> exit출력하고 종료
	만약 exit뒤에 인자가 두개 이상 있으면,
	exit\n
	bash: exit: too many arguments 
	출력후 종료 x
	만약 exit뒤에 숫자가 아니면,
	exit\n
	bash: exit: a: numeric argument required
	출력후 종료
	파이프 뒤에 있으면, 자식프로세스의 exit이기 때문에 쉘 종료 x
	그러나 $?에는 해당 exit의 값이 있음*/
