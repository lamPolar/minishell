/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 04:59:43 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	execute_tree(t_node *root, t_node *ast, t_token *token)
{
	if (root == NULL)
		return ;
	if (root->type == LINE)
		execute_line(root, ast, token);
	else if (root->type == PIPE)
		execute_pipe(root, ast, token);
	else
		printf("wrong ast\n");
}

int	initial_pipe(int process, int ***fd, pid_t **pid)
{
	int i;

	*fd = (int **)ft_calloc(sizeof(int *), process);
	if (*fd == NULL)
		return (1);
	i = 0;
	while (i < process)
	{
		(*fd)[i] = (int *)ft_calloc(sizeof(int), 2);
		if ((*fd)[i] == NULL)
			return (1);
		i += 1;
	}
	// (*fd)[0][FD_READ] = STDIN_FILENO;
	// (*fd)[process - 1][FD_WRITE] = STDOUT_FILENO;
	*pid = (pid_t *)ft_calloc(sizeof(pid_t), process);
	if (*pid == NULL)
		return (1);
	return (0);
}

int	update_exitcode(int status) 
{
	char	*exitcode;
	char	*save;
    t_envp  *env;
	
    env = g_env;
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		exitcode = ft_itoa(status);
		if (exitcode == NULL)
			return (0);
		while (env)
		{
			if (ft_strequal(env->key, "?"))
			{
				save = env->value;
				env->value = exitcode;
				free(save);
				break ;
			}
			env = env->next;
		}
	}
	else
		return (1);
	return (0);
}

int run_builtin(t_node *command, t_node *ast, t_token *token)
{
	if (ft_strequal("pwd", command->str) || ft_strequal("PWD", command->str))
		return (builtin_pwd());
	if (ft_strequal("cd", command->str))
		return (builtin_cd(command));
	if (ft_strequal("exit", command->str))
		return (builtin_exit(command, ast, token));
	if (ft_strequal("env", command->str) || ft_strequal("ENV", command->str))
		return (builtin_env());
	if (ft_strequal("export", command->str))
		return (builtin_export(command->right)); // 얘만 command->right
	if (ft_strequal("echo", command->str) || ft_strequal("ECHO", command->str))
		return (builtin_echo(command));
	if (ft_strequal("unset", command->str))
		return (builtin_unset(command));
	if (check_equal(command->str))
	{
		if (check_invalid(command->str) == 2)
			return (add_to_env_plus(command->str, SHOW));
		else if (check_invalid(command->str) == 0)
			return (add_to_env(command->str, HIDE));
	}
	return (0);
}

int	ft_close(int fd)
{
	int	result;

	result = 0;
	if (fd > 2)
		result = close(fd);
	if (result == -1)
		print_error("KINDER: close failes\n", 0, 0, 0);
	return (result);
}

int	ft_dup2(int fd1, int fd2)
{
	int	result;

	result = 0;
	if (fd1 != fd2)
	{
		result = dup2(fd1, fd2);
		ft_close(fd1);
	}
	if (result < 0)
		print_error("KINDER: dup2 failed\n", 0, 0, 0);
	return (result);
}

void    execute_pipe(t_node *root, t_node *ast, t_token *token)
{
    int **fd;
    pid_t *pid;
    int status;
    int process;
    int i;
    int j;
    t_node *line;
    process = count_process(root);
    if (initial_pipe(process, &fd, &pid))
        return ;
    i = 0;
    while (i < process)
    {
        pid[i] = fork();
        if (pid[i] < 0)
        {
            printf("error\n");
            return ;
        }
        else if (pid[i])
        {
            if (i > 0)
            {
                close(fd[i-1][FD_WRITE]);
                close(fd[i][FD_READ]);
            }
            if (root->right)
                root = root->right;
            i += 1;
            if (i == process -1)
            {
                j = 0;
                while (j < process)
                {
                    waitpid(pid[j], &status, 0);
                    j += 1;
                }
                if (update_exitcode(status)) // 항상 마지막 프로세스 값을 업데이트
                    return ;
            }
        }
        else
        {
            if (i == process -1)
            {
                if (root->right->type == LINE)
                {
                    line = root->right;
                    if (line->left)
                        check_redirection(line->left, fd[i]);
                    if (i > 0)
                    {
                        ft_dup2(fd[i - 1][FD_READ], STDIN_FILENO);
                        ft_close(fd[i - 1][FD_READ]);
                    }
                    ft_dup2(fd[i][FD_WRITE], STDOUT_FILENO);
                    if (line->right)
                    {
                        if (check_builtin(line->right))
                            run_builtin(line->right, ast, token);
                        else
                            execute(line);
                    }
                }
            }
            if (root->left->type == LINE)
            {
                line = root->left;
                if (line->left)
                    check_redirection(line->left, fd[i]);
                if (i != 0)
                {
                    ft_dup2(fd[i - 1][FD_READ], STDIN_FILENO);
                    ft_close(fd[i - 1][FD_READ]);
                }
                ft_dup2(fd[i][FD_WRITE], STDOUT_FILENO);
                ft_close(fd[i][FD_WRITE]);
                if (i != process -1)
                    ft_close(fd[i + 1][FD_READ]);
                if (line->right)
                    {
                        if (check_builtin(line->right))
                            run_builtin(line->right, ast, token);
                        else
                            execute(line);
                    }
            }
        }
    }
}
void    execute_line(t_node *line, t_node *ast, t_token *token)
{
    int save_fd[2];
	int	fd[2];
    pid_t pid;
    int status;

	if (check_builtin(line->right))
	{
		save_fd[0] = dup(STDIN_FILENO);
		save_fd[1] = dup(STDOUT_FILENO);
        check_redirection(line->left, fd);
        if (line->right)
            run_builtin(line->right, ast, token);
		dup2(save_fd[0], STDIN_FILENO);
		dup2(save_fd[1], STDOUT_FILENO);
		close(save_fd[0]);
		close(save_fd[1]);
		//빌트인 정상실행시 -> exitcode update필요
    }
    else
    {
        pid = fork();
        if (pid)
        {
			printf("now\n");
            if (waitpid(pid, &status, 0) == pid)
				update_exitcode(status);
        }
        else
        {
			fd[0] = check_infile(line->left, 0);
			fd[1] = check_outfile(line->left, 1);
			//close (fd[1]);
//			check_redirection(line->left, fd);
            if (line->right)
			{
                execute(line->right);
			}
        }
    }
}




/*
//line이 루트노드일때, 
//1.빌트인인지 확인해
//빌트인이면 리다이렉션 할 때 메인을 유지하기 위한 fd를 저장해줘.(dup(0), dup(1)하고 저장)
//빌트인 바로실행
//끝나면, fd복원
//2. 나머지는 모두 포크가능
//리다이렉션 해주고, 실행
*/

//만약 pipe가 루트노드이면, 
//파이프 연결해
//1. 포크해.
//2. 리다이렉션해
//나머지 필요없는 파이프 제거해
//마지막, root->right 에 대해서 pipe, fork, redirection, execute 진행
