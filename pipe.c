/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/22 23:02:23 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "parse.h"

int	run_pipe(int process, char **command[], t_envp *env)
{
	//t_node *command
	//command : root 기준 왼쪽 : redirection, 오른쪽 : 실제 command
	//1. 총 pipe개수 + 1 = process -> 이건 먼저 알아야해.
	//2. file, command array? list? 
	int		fd[2];
	pid_t	*pid;
	int		i;

	pid = (pid_t *)ft_calloc(sizeof(pid_t), process);
	i = 0;
	while (i < process)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error();
		if (pid[i] == 0)
			// if (root->left->type == 'CMD')
			// {
			// 	ft_command(fd, root, env);
			// }
		if (close(fd[0]) == -1)
			ft_error();
		if (close(fd[1]) == -1)
			ft_error();
	}
	i = 0;
	while (i < process)
		waitpid(pid[i], NULL, 0);
	return (0);
}

//execute : 나누기 (builtin / 실행파일)
void	execute(t_node *command, char **environ)
{
	char	**path_array;
	char	*path;

	//만약 빌트인이면, 빌트인 실행 -> 빌트인 모음과 함께 비교. 빌트인 모음은 어디있지? 전역변수?

	//아니면 command file 찾기
	path = getenv("PATH");
	if (path == NULL)
		ft_error();
	path = find_path(path, command->str);
	if (path == NULL)
		ft_error();
	//execve : command array 로 보내줘야함 -> command list를 다시 array로 만들어?
	if (execve(path, command, environ) == -1)
		ft_error();
}

void	ft_command(int *fd, t_node *command, t_envp *env)
{
	int		infile;
	int		outfile;
	t_node	*redirection;

	infile = STDIN_FILENO;
	outfile = STDOUT_FILENO;
	redirection = command->left;
	while (redirection && redirection->type == REDIRECTION)
	{
		if (redirection->str == '<<')
			infile = open(STDIN_FILENO, O_RDONLY, 0644); //redirection->left->str이 단독으로 들어올때까지 stdin을 읽기
		else if (redirection->str == '<')
			infile = open(redirection->left->str, O_RDONLY, 0644); // left 에 적힌 파일을 읽기
		else if (redirection->str == '>>')
			outfile = open(redirection->left->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (redirection->str == '>')
			outfile = open(redirection->left->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		redirection = redirection->right;
	}
	if (infile == -1 || outfile == -1)
		ft_error();
	if (dup2(infile, STDIN_FILENO) == -1)
		ft_error();
	if (dup2(outfile, STDOUT_FILENO) == -1)
		ft_error();
	
	//어떤 fd를 파이프에 연결해야될지, 어떤 fd를 닫아야할지... 어떻게 알지?
	//해당 cmd가 파이프의 맨앞인지, 가운데인지, 마지막인지 어떻게 알지?
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

//중위순회 방법
//inorder way
void inorder(t_node *root)
{
	//재귀를 돌다가 파이프를 만나면, 파이프를 호출해야하나??
	//그러면 파이프 이전의 명령어를 파이프에 연결해주는건 어떻게 해?
	//아니지; 파이프가 루트고, 파이프를 보고서 왼쪽 오른쪽으로 가니까 괜찮지 않나? 
	//근데...그러면 중위가 아닌데? 전위순회인데? 파이프 - 왼쪽 - 오른쪽 순서니까
	if (root->left) inorder(root->left);
	printf("%s ", root->str);
	printf("%s \n", root->type);
	if (root->right) inorder(root->right);
}

//전위순회 방법 
//preorder way 
void preorder(t_node *root)
{
	printf("%s ", root->str);
	printf("%s \n", root->type);
	if(root->left) preorder(root->left);
	if (root->right) preorder(root->right);
}