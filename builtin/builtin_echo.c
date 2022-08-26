/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:45:54 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/26 16:00:08 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_n(char *str)
{
	int	i;

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

//$? : exit_status출력 : global 로 사용해야할까?
int	builtin_echo(t_node *command, t_envp *env)
{
	int	flag;

	command = command->right;
	flag = 0;
	if (check_n(command->str))
	{
		flag = 1;
		command = command->right;
		while (command && check_n(command->str))
			command = command->right;
	}
	while (command)
	{
		printf("%s", command->right->str);
		command = command->right;
	}
	if (flag)
		printf("\n");
}
	//echo -nnnnnnnnnnnn fdjksl: echo -n fdjksl과 동일하게 취급
	//echo hello ;; 
	//echo hello ; ;  -> syntax error 아니고 그냥 문자출력
	//echo -n -n -n1 >> -n1
	//echo "o"hi"o"