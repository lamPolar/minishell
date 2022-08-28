/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:45:54 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 15:32:11 by heeskim          ###   ########.fr       */
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

int	builtin_echo(t_node *command)
{
	int	flag;

	command = command->right;
	flag = 1;
	if (command && check_n(command->str))
	{
		flag = 0;
		command = command->right;
		while (command && check_n(command->str))
			command = command->right;
	}
	while (command)
	{
		printf("%s", command->str);
		command = command->right;
		if (command)
			printf(" ");
	}
	if (flag)
		printf("\n");
	return (0); //error때문에 삽입
}
