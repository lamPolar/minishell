/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 03:13:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/30 18:21:46 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	execute_function(t_node *command)
{
	if (ft_strequal("pwd", command->str) || ft_strequal("PWD", command->str))
		return (builtin_pwd());
	if (ft_strequal("cd", command->str))
		return (builtin_cd(command));
	if (ft_strequal("exit", command->str))
		return (builtin_exit(command)); // return이 있나..?
	if (ft_strequal("env", command->str) || ft_strequal("ENV", command->str))
		return (builtin_env());
	if (ft_strequal("export", command->str))
		return (builtin_export(command->right)); // 얘만 command->right
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
	execute_process(command);
	return (0);//error로 인한 삽입
}
             
void	execute(t_node *command)
{
	char	**path_array;
	char	**command_array;
	char	*path;
	char	**envp;

	path_array = get_path();
	if (path_array == NULL)
		ft_error();
	path = find_path(path_array, command->str);
	if (path == NULL)
		ft_error();
	command_array = make_command_array(command);
	if (command_array == NULL)
		ft_error();
	envp = dearrange_envp();
	if (envp == NULL)
		exit(EXIT_FAILURE);
	if (execve(path, command_array, envp) == -1)
		ft_error();
}

void	execute_process(t_node *command)
{
	char	**path_array;
	char	**command_array;
	char	*path;
	char	**envp;

	path_array = get_path();
	if (path_array == NULL)
		ft_error();
	path = find_path(path_array, command->str);
	if (path == NULL)
		ft_error();
	command_array = make_command_array(command);
	if (command_array == NULL)
		ft_error();
	envp = dearrange_envp();
	if (envp == NULL)
		exit(EXIT_FAILURE);
	if (execve(path, command_array, envp) == -1)
		ft_error();
}

void	execute_with_fork(t_node *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execute_process(command);
	}
	waitpid(pid, &status, 0);
	update_exitcode(status);
}

void	execute_without_fork(t_node *command)
{
	execute_process(command);
}
