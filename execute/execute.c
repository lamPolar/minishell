/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 03:13:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 11:30:16 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
             
void	execute(t_node *command)
{
	char	**path_array;
	char	**command_array;
	char	*path;
	char	**envp;

	path_array = get_path();
	if (path_array == NULL)
		print_error("KINDER: ", command->str, ": No such file or directory", 0);
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
		print_error("KINDER: execve failed", 0, 0, 0);
}
