/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 15:42:34 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	execute_tree(t_node *root, t_envp *env)
{
	if (root == NULL)
		return ;
	if (root->type == LINE)
		make_process(root, env);
	//ㅇㅕ기서 heredoc이 있으면 먼저 실행
	else if (root->type == PIPE)
		execute_pipe(root, env);
	else
		printf("wrong ast\n");
}

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

int	initial_pipe(int process, int ***fd, pid_t **pid)
{
	int i;

	*fd = (int **)ft_calloc(sizeof(int *), process);
	if (*fd == NULL)
		return (1);
	i = 0;
	while (i < process)
	{
		(*fd)[i] = (int *)ft_calloc(sizeof(int), 2);
		if ((*fd)[i] == NULL)
			return (1);
		i += 1;
	}
	*pid = (pid_t *)ft_calloc(sizeof(pid_t), process);
	if (*pid == NULL)
		return (1);
	return (0);
}

int	update_exitcode(int status, t_envp *env) // 만약 ?를 언셋한 상태라면?
{
	char	*exitcode;
	char	*save;
	
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		exitcode = ft_itoa(status);
		if (exitcode == NULL)
			return (0);
		while (env)
		{
			if (ft_strequal(env->key, "?"))
			{
				save = env->value;
				env->value = exitcode;
				free(save);
				break ;
			}
			env = env->next;
		}
	}
	return (0);
}
//left right를 제대로 확인하고 진입할것
//만약에 left면, 
void	execute_pipe(t_node *root, t_envp *env)
{
	t_node *line;
	int		process;
	int		**fd;
	int		temp_fd[2];
	pid_t	*pid;
	int		status;
	int		i;

	process = count_process(root);
	if (initial_pipe(process, &fd, &pid))
		return ;
	fd[0][FD_READ] = STDIN_FILENO;
	fd[process - 1][FD_WRITE] = STDOUT_FILENO;
	i = 0;
	while (root->type == PIPE)
	{
		i = 0;
 		temp_fd[0] = fd[i][FD_WRITE];
		temp_fd[1] = fd[i+1][FD_READ];
		pipe(temp_fd);
		pid[i] = fork();
		if (pid[i] < 0)
		{
			printf("error\n");
			return ;
		}
		if (pid[i])
		{
			if (root->right)
				root = root->right;
			if (i != 0)
				close(fd[i][FD_READ]);
			close(fd[i][FD_WRITE]);
			i += 1;
		}
		else
		{
			//redirection 진행
			if (i != 0)
			{
				dup2(fd[i - 1][FD_READ], STDIN_FILENO);
				close(fd[i - 1][FD_READ]);
			}
			dup2(fd[i][FD_WRITE], STDOUT_FILENO);
			close(fd[i][FD_WRITE]);
			close(fd[i + 1][FD_READ]);
			close(fd[process -1][FD_WRITE]);
			line = root->left;
			execute_function(line->right, env, 0);
			return ;
		}
	}
	if (root->type == LINE)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			printf("fork error\n");
			return ;
		}
		if (pid[i])
		{
			close(fd[i][FD_READ]);
			if (i != process - 1)
				close(fd[i][FD_WRITE]);
			if (i == process - 1)
			{
				i = 0;
				while (i < process)
				{
					waitpid(pid[i], &status, 0);
					i += 1;
				}
				if (update_exitcode(status, env))
					return ;
			}
		}
		else
		{
			line = root;
			//redirection
			dup2(fd[i - 1][FD_READ], STDIN_FILENO);
			close(fd[i - 1][FD_READ]);
			dup2(fd[i][FD_WRITE], STDOUT_FILENO);
			//자식 프로세스
			execute_function(line->right, env, 0);
			return ;
		}
	}
	else{
		print_node(root);
		printf("root->str : %s, root->type : %d\n", root->str, root->type);
		printf("wrong ast2\n");
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
	{
		execute_function(line->right, env, 1);
	}
	else
		add_to_env("?=0", env, HIDE); //$?만 0으로 초기화
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
