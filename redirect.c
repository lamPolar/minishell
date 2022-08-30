/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:53:49 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 00:22:29 by heeskim          ###   ########.fr       */
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
			open_redirection_file(re->left, HEREDOC, &outfile);
		else if (ft_strequal(re->str, "<"))
			open_redirection_file(re->left, INFILE, &infile);
		else if (ft_strequal(re->str, ">"))
			open_redirection_file(re->left, OUTFILE, &outfile);
		else if (ft_strequal(re->str, ">>"))
			open_redirection_file(re->left, APPEND_OUT, &outfile);
		re = re->right;
	}
	if (infile != STDIN_FILENO)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
			return (1);
		if (close(infile) == -1)
			return (1);
	}
	if (outfile != STDOUT_FILENO)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			return (1);
		if (close(outfile) == -1)
			return (1);
	}
	return (0);
}

void	here_doc(int fd, char *delimiter)
{
	char	*line;
	int		len;

	line = readline("> ");
	while (line)
	{
		if (ft_strequal(delimiter, line))
		{
			free(line);
			break ;
		}
		len = ft_strlen(line);
		write(fd, line, len);
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
}

void	open_redirection_file(t_node *file, int MODE, int *fd)
{
	int temp;

	temp = *fd;
	if (MODE == HEREDOC)
		here_doc(*fd, file->str);
	else if (MODE == INFILE)
		*fd = open(file->str, O_RDONLY, 0644);
	else if (MODE == OUTFILE)
		*fd = open(file->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (MODE == APPEND_OUT)
		*fd = open(file->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (*fd == -1)
	{
		printf("KINDER: %s\n", strerror(errno));
		exit(127);
	}
	if (temp != STDIN_FILENO && temp != STDOUT_FILENO)
		close(temp);
}
