/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:53:49 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/02 17:51:43 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	check_redirection(t_node *re, int *infd, int *outfd)
{
	while (re && re->type == REDIRECTION)
	{
		if (ft_strequal(re->str, "<") || ft_strequal(re->str, "<<"))
		{
			if (check_infile(re, infd))
				return (1);
		}
		else if (ft_strequal(re->str, ">") || ft_strequal(re->str, ">>"))
		{
			if (check_outfile(re, outfd))
				return (1);
		}
		re = re->right;
	}
	return (0);
}

int	check_infile(t_node *re, int *infd)
{
	if (ft_strequal(re->str, "<"))
	{
		if (re->left->str[0] == '\0')
			return (print_fd_error(AMBIGUOUS, infd));
		ft_close(*infd);
		*infd = open(re->left->str, O_RDONLY, 0644);
	}
	else if (ft_strequal(re->str, "<<"))
	{
		ft_close(*infd);
		check_here_doc(infd, re->left->str);
	}
	if (*infd == -1)
		return (print_fd_error(OPEN_ERR, infd));
	return (0);
}

int	check_outfile(t_node *re, int *outfd)
{
	if (ft_strequal(re->str, ">"))
	{
		if (re->left->str[0] == '\0')
			return (print_fd_error(AMBIGUOUS, outfd));
		ft_close(*outfd);
		*outfd = open(re->left->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else if (ft_strequal(re->str, ">>"))
	{
		if (re->left->str[0] == '\0')
			return (print_fd_error(AMBIGUOUS, outfd));
		ft_close(*outfd);
		*outfd = open(re->left->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	if (*outfd == -1)
		return (print_fd_error(OPEN_ERR, outfd));
	return (0);
}

void	check_here_doc(int *infd, char *delimiter)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
 	signal(SIGINT, signal_heredoc);
	signal(SIGQUIT, signal_heredoc);
	pid = fork();
	if (pid)
	{
		ft_close(fd[1]);
		waitpid(pid, &status, 0);
		*infd = fd[0];
		update_exitcode(status);
	}
	else
		here_doc(fd, delimiter);
}

void	here_doc(int *fd, char *delimiter)
{
	char	*buf;
	char	*line;

	ft_close(fd[0]);
	buf = (char *)ft_calloc(sizeof(char), 1);
	line = readline("\e[0;91m> \e[0m");
	while (line)
	{
		if (ft_strequal(delimiter, line))
		{
			write(fd[1], buf, ft_strlen(buf));
			free(buf);
			exit(0);
		}
		buf = ft_strjoin(buf, line, 1);
		buf = ft_strjoin(buf, ft_strdup("\n"), 1);
		line = readline("\e[0;91m> \e[0m");
	}
}
