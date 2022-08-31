/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 17:06:44 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	initial_pipe(int process, int **pipes, pid_t **pid, t_node **line)
{
	int	i;

	*line = NULL;
	*pipes = (int *)ft_calloc(sizeof(int), (process - 1) * 2);
	if (*pipes == NULL)
		return (1);
	i = 0;
	while (i < process - 1)
	{
		pipe((*pipes) + (i * 2));
		i += 1;
	}
	*pid = (pid_t *)ft_calloc(sizeof(pid_t), process);
	if (*pid == NULL)
		return (1);
	return (0);
}

void	close_pipe(int process, int *pipes)
{
	int	i;

	i = 0;
	while (i < process -1)
	{
		close(pipes[i * 2]);
		close(pipes[(i * 2) + 1]);
		i += 1;
	}
}

t_node	*child_process(int *pipes, int i, int process, t_node *root)
{
	t_node	*line;
	int		fd[2];

	line = NULL;
	if (i != process -1)
		line = root->left;
	else if (i == process - 1)
		line = root;
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (i != 0)
		fd[0] = pipes[(i - 1) * 2];
	if (i != process - 1)
		fd[1] = pipes[(i * 2) + 1];
	fd[0] = check_infile(line->left, fd[0]);
	fd[1] = check_outfile(line->left, fd[1]);
	ft_dup2(fd[0], 0);
	ft_dup2(fd[1], 1);
	return (line);
}

void	parent_process(int *pipes, pid_t *pid, int i, int process)
{
	int	status;
	int	j;

	if (i == process - 1)
	{
		close_pipe(process, pipes);
		j = 0;
		while (j < process)
		{
			wait(&status);
			j += 1;
			if (waitpid(pid[process - 1], &status, 0) == pid[process - 1])
			{
				update_exitcode(status);
				j += 1;
			}
		}
	}
}
