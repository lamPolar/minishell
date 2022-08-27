/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 01:09:53 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

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

void	make_process(t_node *line, t_envp *env)
{
	//pid_t	pid;
	int		fd[2];
	int		status;
	char	*exitcode;

	//pid = fork();
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	//if (pid == 0)
	//{
	if (line->left)
		check_redirection(line->left, fd);
	if (line->right)
		execute_function(line->right, env);
	//}
	//waitpid(pid, &status, 0);
	// if (WIFEXITED(status))
    // {
    //     status = WEXITSTATUS(status);       
    //     exitcode = ft_itoa(status);
	// 	if (exitcode == NULL)
	// 		return ;
	// 	exitcode = ft_strjoin("?=", exitcode, 0);
	// 	if (exitcode == NULL)
	// 		return ;
	// 	if (add_to_env(exitcode, env))
	// 		return ;
    // }
}

void	execute_tree(t_node *root, t_envp *env)
{
	int process;
	
	process = count_process(root);
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

char	**make_command_array(t_node *command)
{
	int		size;
	int		i;
	char	**command_array;
	t_node	*save;

	size = 0;
	save = command;
	while (command)
	{
		size += 1;
		command = command->right;
	}
	command_array = (char **)ft_calloc(sizeof(char *), size + 1);
	if (command_array == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		command_array[i] = ft_strdup(save->str);
		if (command_array[i] == NULL)
		{
			free_double_array(command_array);
			return (NULL);
		}
		i += 1;
		save = save->right;
	}
	return (command_array);
}

int	execute_function(t_node *command, t_envp *env)
{
	if (ft_strequal("pwd", command->str) || ft_strequal("PWD", command->str))
		return (builtin_pwd(command));
	else if (ft_strequal("cd", command->str))
		return (builtin_cd(command, env));
	else if (ft_strequal("exit", command->str))
		return (builtin_exit(command, env));
	else if (ft_strequal("env", command->str) || \
			ft_strequal("ENV", command->str))
		return (builtin_env(env));
	else if (ft_strequal("export", command->str))
		return (builtin_export(command, env));
	else if (ft_strequal("echo", command->str) || \
			ft_strequal("ECHO", command->str))
		return (builtin_echo(command, env));
	else if (ft_strequal("unset", command->str))
		return (builtin_unset(command, env));
	else
		execute(command, env);
	//만약에 OMG=omg 명령어가 들어왔다면, add_env해주고, display = HIDE로 설정
}

void	execute(t_node *command, t_envp *env)
{
	pid_t	pid;
	int		status;
	char	*exitcode;
	char	**path_array;
	char	**command_array;
	char	*path;
	char	**envp;

	pid = fork();
	if (pid == 0)
	{
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
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
    {
        status = WEXITSTATUS(status);       
        exitcode = ft_itoa(status);
		if (exitcode == NULL)
			return ;
		exitcode = ft_strjoin("?=", exitcode, 0);
		if (exitcode == NULL)
			return ;
		if (add_to_env(exitcode, env))
			return ;
    }
}
