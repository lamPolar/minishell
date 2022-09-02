/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:11:19 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/02 13:38:07 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	execute_function(t_node *line, t_node *ast, t_token *token)
{
	if (line->right && check_builtin(line->right))
	{
		if (run_builtin(line->right, ast, token))
			exit(1);
		else
			exit(0);
	}
	else
	{
		if (line->right)
			execute(line->right);
		exit(0);
	}
}

void	execute(t_node *command)
{
	char	**path_array;
	char	**command_array;
	char	*path;
	char	**envp;

	path_array = get_path();
	if (path_array == NULL || path_array[0] == NULL)
	{
		print_error("KINDER: ", command->str, ": No such file or directory", 0);
		return ;
	}
	path = find_path(path_array, command->str);
	if (path == NULL)
		return ;
	command_array = make_command_array(command);
	if (command_array == NULL)
		return ;
	envp = dearrange_envp();
	if (envp == NULL)
		exit(EXIT_FAILURE);
	if (execve(path, command_array, envp) == -1)
	{
		print_error("KINDER: Execute failed", 0, 0, 0);
		exit(126);
	}
}
