/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:45:54 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/25 17:54:09 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int check_n(char *str)
{
	int i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i += 1;
	}
	return (1);
}

int builtin_echo(t_node *command, t_envp *env)
{
	int flag;

	command = command->right;
	//echo에는 -n옵션만 있음
	//-> 만약에 인자가 -n이거나 -nnn...이 아닐경우 모두 일반출력
	flag = 0;
	if (check_n(command->str))
	{
		flag = 1;
		command = command->right;
		while (command && check_n(command->str))
			command = command->right;
	}
	//-n 옵션 : newline character을 제외하고 출력 : 마지막 개행만 없애면 되나?
	//$? : exit_status출력 : global 로 사용해야할까?
	while (command)
	{
		printf("%s", command->right->str);
		command = command->right;
	}
	//전체 그대로 출력
	if (flag)
		printf("\n");
}
	//echo -nnnnnnnnnnnn fdjksl: echo -n fdjksl과 동일하게 취급
	//echo hello ;; 
	//echo hello ; ;  -> syntax error 아니고 그냥 문자출력
	//echo -n -n -n1 >> -n1
	//echo "o"hi"o"