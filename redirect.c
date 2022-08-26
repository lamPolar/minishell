/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:53:49 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/26 16:14:06 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "parse.h"
#include "builtin.h"

void	check_redirection(t_node *re, int fd[2])
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
	if (dup2(infile, STDIN_FILENO) == -1)
	//만약 infile == STDIN_FILENO면?
		ft_error();
	if (dup2(outfile, STDOUT_FILENO) == -1)
	//oufile == STDOUT_FILENO 면?
		ft_error();
	if (close(infile) == -1)
		ft_error();
	if (close(outfile) == -1)
		ft_error();
}
//나머지 fd처리 어떻게 할건지?

void	here_doc(int fd, char *delimiter)
{
	char	*line;
	int		i;
	int		len;

	line = readline("HERE_DOC > ");
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
		line = readline("HERE_DOC > ");
	}
}

//여기 디벨롭 방법 : stat으로 접근가능한 권한 확인 후 / open시 권한 할당
int	open_redirection_file(t_node *file, int MODE, int *fd)
{
	if (MODE == HEREDOC)
	{
		//*fd = open(STDIN_FILENO, O_RDONLY, 0644);
		//여기서 보내는 fd는 현재의 outfd
		here_doc(*fd, file->str);
		//str이 단독으로 들어올때까지 stdin을 읽기 >> 어떻게 하지
	}
	else if (MODE == INFILE)
		*fd = open(file->str, O_RDONLY, 0644);
	else if (MODE == OUTFILE)
		*fd = open(file->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (MODE == APPEND_OUT)
		*fd = open(file->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (*fd == -1)
		printf("KINDER: %s", strerror(errno));
}
