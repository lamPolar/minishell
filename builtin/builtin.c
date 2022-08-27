/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:31:56 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 00:45:23 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

int	builtin_exit(t_node *line, t_envp *env)
{
	t_node	*argument;

	argument = line->right;
	if (argument == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		if (argument->right == NULL)
		{
			if (ft_isnum(argument->str))
				exit(ft_atoi(argument->str));
			else
			{
				printf("exit\nKINDER: exit: %s: numeric argument required\n", \
						argument->str);
				free_envp(env);
				//free_tree(head);
				exit(255);
			}
		}
		else
			printf("exit\nKINDER: exit: too many arguments\n");
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

	//exit하기 전에 exitcode를 env에 저장하기로 xx-> wait에서 끝난 process의 종료코드를 보고, 그걸 읽어서 env에 넣어주기로
	