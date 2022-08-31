/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 03:13:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 17:12:01 by heeskim          ###   ########.fr       */
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
	int		fd[2];
	int		status;

	if (check_builtin(line->right))
		execute_builtin(line, ast, token);
	else
	{
		if (fork())
		{
			if (wait(&status))
				update_exitcode(status);
		}
		else
		{
			fd[0] = STDIN_FILENO;
			fd[1] = STDOUT_FILENO;
			fd[0] = check_infile(line->left, fd[0]);
			fd[1] = check_outfile(line->left, fd[1]);
			ft_dup2(fd[0], STDIN_FILENO);
			ft_dup2(fd[1], STDOUT_FILENO);
			if (line->right)
				execute(line->right);
		}
	}
}

void	execute_builtin(t_node *line, t_node *ast, t_token *token)
{
	int	save_fd[2];
	int	fd[2];

	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	fd[0] = check_infile(line->left, fd[0]);
	fd[1] = check_outfile(line->left, fd[1]);
	ft_dup2(fd[0], STDIN_FILENO);
	ft_dup2(fd[1], STDOUT_FILENO);
	if (line->right)
	{
		if (run_builtin(line->right, ast, token))
			signal_exit_code(ft_strdup("1"));
		else
			signal_exit_code(ft_strdup("0"));
	}	
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
}
