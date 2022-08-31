/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:53:49 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 15:26:50 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	check_redirection(t_node *re, int fd[2])
{
	int		infile;
	int		outfile;

	infile = fd[0];
	outfile = fd[1];
	while (re && re->type == REDIRECTION)
	{
		if (ft_strequal(re->str, "<<"))
			open_redirection_file(re->left, HEREDOC, outfile);
		else if (ft_strequal(re->str, "<"))
			infile = open_redirection_file(re->left, INFILE, infile);
		else if (ft_strequal(re->str, ">"))
			outfile = open_redirection_file(re->left, OUTFILE, outfile);
		else if (ft_strequal(re->str, ">>"))
			outfile = open_redirection_file(re->left, APPEND_OUT, outfile);
		re = re->right;
	}
	if (infile != STDIN_FILENO)
		ft_dup2(infile, STDIN_FILENO);
	if (outfile != STDOUT_FILENO)
		ft_dup2(outfile, STDOUT_FILENO);
	return (0);
}

int	check_infile(t_node *re, int fd)
{
	int	infile;

	infile = fd;
	while (re && re->type == REDIRECTION)
	{
		if (ft_strequal(re->str, "<"))
			infile = open(re->left->str, O_RDONLY, 0644);
		// else if (ft_strequal(re->str, "<<"))
		// {
		// 	close(infile);
		// }
		ft_close(fd);
		fd = infile;
		re = re->right;
	}
	if (fd != STDIN_FILENO)
		ft_dup2(fd, STDIN_FILENO);
	return (0);
}

int	check_outfile(t_node *re, int fd)
{
	int	outfile;

	outfile = fd;
	while (re && re->type == REDIRECTION)
	{
		if (ft_strequal(re->str, "<<"))
			here_doc(fd, re->left->str);
		else if (ft_strequal(re->str, ">"))
			outfile = open(re->left->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (ft_strequal(re->str, ">>"))
			outfile = open(re->left->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
		ft_close(fd);
		fd = outfile;
		re = re->right;
	}
	ft_dup2(fd, STDOUT_FILENO);
	return (0);
}

void	here_doc(int fd, char *delimiter)
{
	char	*line;
	char	*buf;

	buf = (char *)ft_calloc(sizeof(char), 1);
	line = readline("> ");
	while (line)
	{
		if (ft_strequal(delimiter, line))
		{
			write(fd, buf, ft_strlen(buf));
			free(buf);
			break ;
		}
		buf = ft_strjoin(buf, line, 1);
		buf = ft_strjoin(buf, ft_strdup("\n"), 1);
		line = readline("> ");
	}
}

int	open_redirection_file(t_node *file, int MODE, int fd)
{
	int	temp;

	if (MODE == HEREDOC)
	{
		here_doc(fd, file->str);
		return (0);
	}
	else if (MODE == INFILE)
	{
		// if (fd != STDIN_FILENO)
		// 	close(fd);
		temp = open(file->str, O_RDONLY, 0644);
	}
	else if (MODE == OUTFILE)
	{
		// if (fd != STDOUT_FILENO)
		// 	close(fd);
		temp = open(file->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else if (MODE == APPEND_OUT)
	{
		// if (fd != STDOUT_FILENO)
		// 	close(fd);
		temp = open(file->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	else
		temp = -1;
	if (temp == -1)
	{
		printf("KINDER: %s\n", strerror(errno));
		exit(127);
	}
	return (temp);
}
