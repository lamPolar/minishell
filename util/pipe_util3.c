/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:46:17 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 15:18:52 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

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

int	run_builtin(t_node *command, t_node *ast, t_token *token)
{
	if (ft_strequal("pwd", command->str) || ft_strequal("PWD", command->str))
		return (builtin_pwd());
	if (ft_strequal("cd", command->str))
		return (builtin_cd(command));
	if (ft_strequal("exit", command->str))
		return (builtin_exit(command, ast, token));
	if (ft_strequal("env", command->str) || ft_strequal("ENV", command->str))
		return (builtin_env());
	if (ft_strequal("export", command->str))
		return (builtin_export(command->right));
	if (ft_strequal("echo", command->str) || ft_strequal("ECHO", command->str))
		return (builtin_echo(command));
	if (ft_strequal("unset", command->str))
		return (builtin_unset(command));
	if (check_equal(command->str))
	{
		if (check_invalid(command->str) == 2)
			return (add_to_env_plus(command->str, SHOW));
		else if (check_invalid(command->str) == 0)
			return (add_to_env(command->str, HIDE));
	}
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
