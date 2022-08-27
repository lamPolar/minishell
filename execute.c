/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 03:13:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 04:47:19 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	execute_function(t_node *command, t_envp *env)
{
	if (ft_strequal("pwd", command->str) || ft_strequal("PWD", command->str))
		return (builtin_pwd(command));
	if (ft_strequal("cd", command->str))
		return (builtin_cd(command, env));
	if (ft_strequal("exit", command->str))
		return (builtin_exit(command, env));
	if (ft_strequal("env", command->str) || ft_strequal("ENV", command->str))
		return (builtin_env(env));
	if (ft_strequal("export", command->str))
		return (builtin_export(command->right, env)); // 얘만 command->right
	if (ft_strequal("echo", command->str) || ft_strequal("ECHO", command->str))
		return (builtin_echo(command, env));
	if (ft_strequal("unset", command->str))
		return (builtin_unset(command, env));
	if (check_equal(command->str))
	{
		if (check_invalid(command->str) == 2)
			return (add_to_env_plus(command->str, env, SHOW));
		else if (check_invalid(command->str) == 0)
			return (add_to_env(command->str, env, HIDE));
	}
	execute_with_fork(command, env);
}
               
void	execute_process(t_node *command, t_envp *env)
{
	char	**path_array;
	char	**command_array;
	char	*path;
	char	**envp;

	path_array = get_path(env);
	if (path_array == NULL)
		ft_error();
	path = find_path(path_array, command->str);
	if (path == NULL)
		ft_error();
	command_array = make_command_array(command);
	if (command_array == NULL)
		ft_error();
	envp = dearrange_envp(env);
	if (envp == NULL)
		exit(EXIT_FAILURE);
	if (execve(path, command_array, envp) == -1)
		ft_error();
}

void	execute_with_fork(t_node *command, t_envp *env)
{
	pid_t	pid;
	int		status;
	char	*exitcode;

	pid = fork();
	if (pid == 0)
	{
		execute_process(command, env);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		exitcode = ft_itoa(status);
		if (exitcode == NULL)
			return ;
		while (env)
		{
			if (ft_strequal(env->key, "?"))
				change_env_value(exitcode, env, HIDE);
			env = env->next;
		}
	}
}
