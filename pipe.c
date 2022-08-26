/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/26 16:43:40 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "builtin.h"
#include "parse.h"

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

	//t_node *command
	//command : root 기준 왼쪽 : redirection, 오른쪽 : 실제 command
	//1. 총 pipe개수 + 1 = process -> 이건 먼저 알아야해.
	//2. file, command array? list? 
int	run_pipe(t_node *root, t_envp *env)
{
	int		fd[2];
	pid_t	*pid;
	int		i;
	int		process;

	process = count_process(root);
	pid = (pid_t *)ft_calloc(sizeof(pid_t), process);
	i = 0;
	while (i < process)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error();
		if (pid[i] == 0)
			ft_command(fd, root->right, env);
		if (close(fd[0]) == -1)
			ft_error();
		if (close(fd[1]) == -1)
			ft_error();
	}
	i = 0;
	while (i < process)
		waitpid(pid[i], NULL, 0);
	return (0);
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
	i = 0;
	while (i < size)
	{
		command_array[i] = ft_strdup(save->str);
		i += 1;
		save = save->right;
	}
}

char	**dearrange_envp(t_envp *env)
{
	char	**envp;
	int		size;
	int		i;

	size = get_env_size(env);
	envp = (char **)ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (i < size)
	{
		if (env->display == SHOW)
		{	
			envp[i] == ft_strjoin_three(env->key, "=", env->value);
			if (envp[i] == NULL)
			{
				free_double_array(envp);
				return (NULL);
			}
			i += 1;
		}
		env = env->next;
	}
}

void	execute(t_node *command, t_envp *env)
{
	char	**path_array;
	char	**command_array;
	char	*path;
	char	**envp;

	//아니면 command file 찾기
	path = getenv("PATH");
	if (path == NULL)
		ft_error();
	path = find_path(path, command->str);
	if (path == NULL)
		ft_error();
	command_array = make_command_array(command);
	envp = dearrange_envp(env);
	if (envp == NULL)
		exit(EXIT_FAILURE);
	if (execve(path, command, envp) == -1)
		ft_error();
}

int	get_env_size(t_envp *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->display == SHOW)
			i += 1;
		env = env->next;
	}
	return (i);
}

void	ft_command(int *fd, t_node *line, t_envp *env)
{
	int		fd[2];
	t_node	*redirection;
	t_node	*command;

	redirection = line->left;
	command = line->right;
	check_redirection(redirection, fd);
	//execute : 나누기 (builtin / 실행파일)
	execute_function(command, env);
	//fd 정리 필요 redirection에 어떤 fd2개를 연결시켜줄지?
	//어떤 fd를 파이프에 연결해야될지, 어떤 fd를 닫아야할지... 어떻게 알지?
	//해당 cmd가 파이프의 맨앞인지, 가운데인지, 마지막인지 어떻게 알지?
}

//전위순회 방법 
//preorder way 
// void	preorder(t_node *root)
// {
// 	printf("%s ", root->str);
// 	printf("%s \n", root->type);
// 	if(root->left)
// 		preorder(root->left);
// 	if (root->right)
// 		preorder(root->right);
// }

int	execute_function(t_node *command, t_envp *env)
{
	int	fd[2];

	if (ft_strequal("pwd", command->str) == 0)
		return (builtin_pwd(command));
	else if (ft_strequal("cd", command->str) == 0)
		return (builtin_cd(command, env));
	else if (ft_strequal("exit", command->str) == 0)
		return (builtin_exit(command));
	else if (ft_strequal("env", command->str) == 0)
		return (builtin_env(env));
	else if (ft_strequal("export", command->str) == 0)
		return (builtin_export(command, env));
	else if (ft_strequal("echo", command->str) == 0)
		return (builtin_echo(command, env));
	else if (ft_strequal("unset", command->str) == 0)
		return (builtin_unset(command, env));
	//빌트인이 아니면, execute로 fork실행
	else
		execute(command, env);
	return (0);
}
