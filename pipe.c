/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 03:40:48 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	execute_tree(t_node *root, t_envp *env)
{
	int	process;

	process = count_process(root);
	//ㅇㅕ기서 heredoc이 있으면 먼저 실행
	if (root->type == LINE)
	{
		make_process(root, env);
	}
	if (root->type == PIPE)
	{
		execute_tree(root->left, env);
		execute_tree(root->right, env);
	}	
}

void	make_process(t_node *line, t_envp *env)
{
	int		fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (line->left)
		check_redirection(line->left, fd);
	if (line->right)
		execute_function(line->right, env);
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
