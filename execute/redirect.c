/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:53:49 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/02 00:53:36 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	print_fd_error(int flag)
{
	if (flag == 1)
	{
		print_error("KINDER: ambiguous redirect", 0, 0, 0);
		return (-1);
	}
	if (flag == 2)
	{
		print_error("KINDER: %s\n", strerror(errno), 0, 0);
		return (-2);
	}
	return (0);
}

int	check_infile(t_node *re, int fd)
{
	int	infile;

	infile = fd;
	while (re && re->type == REDIRECTION)
	{
		if (ft_strequal(re->str, "<") || ft_strequal(re->str, "<<"))
		{
			if (ft_strequal(re->str, "<"))
			{
				if (re->left->str[0] == '\0')
					return (print_fd_error(1));
				infile = open(re->left->str, O_RDONLY, 0644);
			}
			else if (ft_strequal(re->str, "<<"))
				infile = STDIN_FILENO;
			if (infile == -1)
				return (print_fd_error(2));
			ft_close(fd);
			fd = infile;
		}
		re = re->right;
	}
	return (fd);
}

int	check_outfile_detail(t_node *re, int fd)
{
	int	outfile;

	outfile = fd;
	if (ft_strequal(re->str, ">"))
	{
		if (re->left->str[0] == '\0')
			return (print_fd_error(1));
		outfile = open(re->left->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else if (ft_strequal(re->str, ">>"))
	{
		if (re->left->str[0] == '\0')
			return (print_fd_error(1));
		outfile = open(re->left->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	if (outfile == -1)
		return (print_fd_error(2));
	ft_close(fd);
	return (outfile);
}

int	check_outfile(t_node *re, int fd)
{
	while (re && re->type == REDIRECTION)
	{
		if (ft_strequal(re->str, "<<"))
			here_doc(fd, re->left->str);
		else if (ft_strequal(re->str, ">") || ft_strequal(re->str, ">>"))
		{
			fd = check_outfile_detail(re, fd);
			if (fd == -1 || fd == -2)
				return (fd);
		}
		re = re->right;
	}
	return (fd);
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
