#include "builtin/builtin.h"	

int	run_pipe(t_node *root, t_envp *env)
{
	int		fd[2];
	pid_t	*pid;
	int		i;
	int		process;
	t_node	*line;

	//fd 정리 필요 redirection에 어떤 fd2개를 연결시켜줄지?
	//어떤 fd를 파이프에 연결해야될지, 어떤 fd를 닫아야할지... 어떻게 알지?
	//해당 cmd가 파이프의 맨앞인지, 가운데인지, 마지막인지 어떻게 알지?
	process = count_process(root);
	pid = (pid_t *)ft_calloc(sizeof(pid_t), process);
	i = 0;
	if (process == 1)
	{
		//파이프 없이 포크후
		//빌트인이면 빌트인 실행
		//실행파일이면 execve
		return (0);
	}
	while (i < process)
	{
		if (i == process - 1)
			line = root->right;
		else
			line = root->left;
		root = root->right;
		if (pipe(fd) == -1)
			ft_error();
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error();
		if (pid[i] == 0)
			ft_command(line, env);
		if (close(fd[0]) == -1)
			ft_error();
		if (close(fd[1]) == -1)
			ft_error();
	}
	i = 0;
	while (i < process)
		waitpid(pid[i], NULL, 0);
}

void	ft_command(t_node *line, t_envp *env)
{
	int		fd[2];
	t_node	*redirection;
	t_node	*command;

	redirection = line->left;
	command = line->right;
	if (check_redirection(redirection, fd)) // 함수 내부에서 바로 exit할지
		exit(EXIT_FAILURE); // 아니면 여기서 exit할지
		//뭐라도 프린트 해야할지?
	execute_function(command, env);
}
