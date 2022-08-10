/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/07/02 13:58:38 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc < 5 || argc > 5 || argv == NULL)
		return (0);
	if (pipe(fd) == -1)
		ft_error();
	pid1 = fork();
	if (pid1 == -1)
		ft_error();
	if (pid1 == 0)
		ft_first_command(fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		ft_error();
	if (pid2 == 0)
		ft_second_command(fd, argv, envp);
	if (close(fd[0]) == -1)
		ft_error();
	if (close(fd[1]) == -1)
		ft_error();
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

void	execute(char *argv, char **environ)
{
	char	**path_array;
	char	*path;
	char	**command_array;

	command_array = ft_split(argv, ' ');
	if (command_array == NULL)
		ft_error();
	path_array = get_path(environ);
	if (path_array == NULL)
		ft_error();
	path = find_path(path_array, command_array[0]);
	if (path == NULL)
		ft_error();
	if (execve(path, command_array, environ) == -1)
		ft_error();
}

void	ft_first_command(int *fd, char *argv[], char *envp[])
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0744);
	if (infile == -1)
		ft_error();
	if (dup2(infile, STDIN_FILENO) == -1)
		ft_error();
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error();
	if (close(infile) == -1)
		ft_error();
	if (close(fd[0]) == -1)
		ft_error();
	if (close(fd[1]) == -1)
		ft_error();
	execute(argv[2], envp);
}

void	ft_second_command(int *fd, char *argv[], char *envp[])
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0744);
	if (outfile == -1)
		ft_error();
	if (dup2(outfile, STDOUT_FILENO) == -1)
		ft_error();
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error();
	if (close(outfile) == -1)
		ft_error();
	if (close(fd[0]) == -1)
		ft_error();
	if (close(fd[1]) == -1)
		ft_error();
	execute(argv[3], envp);
}
