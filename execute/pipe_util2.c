/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:46:17 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 11:30:47 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	print_node(t_node *root)
{
	if (root->papa != NULL)
		printf("papa : %d / %s\n", root->papa->type, root->papa->str);
	printf("str : %s ", root->str);
	printf("type : %d \n", root->type);
	if (root->left)
	{
		printf("<");
		print_node(root->left);
	}
	if (root->right)
	{
		printf(">");
		print_node(root->right);
	}
}

int	check_builtin(t_node *command)
{
	if (ft_strequal(command->str, "echo"))
		return (1);
	 if (ft_strequal(command->str, "exit"))
		return (1);
	 if (ft_strequal(command->str, "env"))
		return (1);
	 if (ft_strequal(command->str, "pwd"))
		return (1);
	 if (ft_strequal(command->str, "cd"))
		return (1);
	 if (ft_strequal(command->str, "unset"))
		return (1);
	 if (ft_strequal(command->str, "export"))
		return (1);
	return (0);
}

int	count_process(t_node *root)
{
	int	i;

	i = 1;
	while (root->type == PIPE)
	{
		i += 1;
		root = root->right;
	}
	return (i);
}

int	get_command_size(t_node *command)
{
	int	size;

	size = 0;
	while (command)
	{
		size += 1;
		command = command->right;
	}
	return (size);
}

char	**make_command_array(t_node *command)
{
	int		size;
	int		i;
	char	**command_array;

	size = get_command_size(command);
	command_array = (char **)ft_calloc(sizeof(char *), size + 1);
	if (command_array == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		command_array[i] = ft_strdup(command->str);
		if (command_array[i] == NULL)
		{
			free_double_array(command_array);
			return (NULL);
		}
		i += 1;
		command = command->right;
	}
	return (command_array);
}
