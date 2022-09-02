/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 03:13:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/02 17:51:53 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	execute_tree(t_node *root, t_node *ast, t_token *token)
{
	int	process;

	if (root->type == LINE)
		execute_line(root, ast, token);
	else if (root->type == PIPE)
	{
		process = count_process(root);
		execute_pipe(root, ast, token, process);
	}
	else
		print_error("KINDER: Wrong AST", 0, 0, 0);
}

void	execute_pipe(t_node *root, t_node *ast, t_token *token, int process)
{
	int		i;
	t_node	*line;
	int		*pipes;
	pid_t	*pid;

	if (initial_pipe(process, &pipes, &pid, &line))
		return ;
	i = 0;
	signal(SIGINT, sigint_inpipe);
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
			parent_process(pipes, pid, i++, process);
			if (root->right)
				root = root->right;
		}
	}
}

void	execute_executable(t_node *line)
{
	int	fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (check_redirection(line->left, &fd[0], &fd[1]))
		check_fd_error(fd, 1);
	ft_dup2(fd[0], STDIN_FILENO);
	ft_dup2(fd[1], STDOUT_FILENO);
	if (line->right)
		execute(line->right);
	exit(0);
}

void	execute_line(t_node *line, t_node *ast, t_token *token)
{
	pid_t	pid;
	int		save_fd[2];
	int		status;

	if (line->right && check_builtin(line->right))
	{
		save_fd[0] = dup(STDIN_FILENO);
		save_fd[1] = dup(STDOUT_FILENO);
		execute_builtin(line, ast, token);
		ft_dup2(save_fd[0], STDIN_FILENO);
		ft_dup2(save_fd[1], STDOUT_FILENO);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pid = fork();
		if (pid)
		{
			if (waitpid(pid, &status, 0) == pid)
				update_exitcode(status);
		}
		else
		{
			signal(SIGINT, signal_handler);
			signal(SIGQUIT, signal_handler);
			execute_executable(line);
		}
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
	}
}

void	execute_builtin(t_node *line, t_node *ast, t_token *token)
{
	int	fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (check_redirection(line->left, &fd[0], &fd[1]))
	{
		check_fd_error(fd, 0);
		return ;
	}
	ft_dup2(fd[0], STDIN_FILENO);
	ft_dup2(fd[1], STDOUT_FILENO);
	if (run_builtin(line->right, ast, token))
		signal_exit_code(ft_strdup("1"));
	else
		signal_exit_code(ft_strdup("0"));
}
