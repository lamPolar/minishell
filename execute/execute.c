/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 03:13:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 15:38:00 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	execute_tree(t_node *root, t_node *ast, t_token *token)
{
	if (root->type == LINE)
		execute_line(root, ast, token);
	else if (root->type == PIPE)
		execute_pipe(root, ast, token);
	else
		print_error("KINDER: Wrong AST", 0, 0, 0);
}

void	execute_pipe(t_node *root, t_node *ast, t_token *token)
{
	int		i;
	t_node	*line;
	int		*pipes;
	pid_t	*pid;
	int		process;

	line = NULL;
	process = count_process(root);
	if (initial_pipe(process, &pipes, &pid))
		return ;
	i = 0;
	while (i < process)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			line = child_process(pipes, i, process, root);
			close_pipe(process, pipes);
			execute_function(line, ast, token);
		}
		else
		{
			parent_process(pipes, pid, i, process);
			if (root->right)
				root = root->right;
			i += 1;
		}
	}
}

void	execute_line(t_node *line, t_node *ast, t_token *token)
{
	int		save_fd[2];
	int		fd[2];
	pid_t	pid;
	int		status;

	if (check_builtin(line->right))
	{
		save_fd[0] = dup(STDIN_FILENO);
		save_fd[1] = dup(STDOUT_FILENO);
		//check_redirection(line->left, fd);
		if (line->right)
			run_builtin(line->right, ast, token);
		dup2(save_fd[0], STDIN_FILENO);
		dup2(save_fd[1], STDOUT_FILENO);
		close(save_fd[0]);
		close(save_fd[1]);
		//빌트인 정상실행시 -> exitcode update필요
	}
	else
	{
		pid = fork();
		if (pid)
		{
			if (waitpid(pid, &status, 0) == pid)
				update_exitcode(status);
		}
		else
		{
			fd[0] = STDIN_FILENO;
			fd[1] = STDOUT_FILENO;
			//fd[0] = check_infile(line->left, STDIN_FILENO);
			//fd[1] = check_outfile(line->right, STDOUT_FILENO);
			// check_redirection(line->left, fd);
			ft_dup2(fd[0], STDIN_FILENO);
			ft_dup2(fd[1], STDOUT_FILENO);
			if (line->right)
			{
				execute(line->right);
			}
		}
	}
}

void	execute_function(t_node *line, t_node *ast, t_token *token)
{
	if (check_builtin(line->right))
	{
		run_builtin(line->right, ast, token);
		exit(0);
	}
	else
	{
		if (line->right)
			execute(line->right);
	}
}

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
