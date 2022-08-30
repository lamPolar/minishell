/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/30 17:09:12 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	execute_tree(t_node *root, t_envp *env)
{
	if (root == NULL)
		return ;
	if (root->type == LINE)
		execute_line(root, env);
	//ㅇㅕ기서 heredoc이 있으면 먼저 실행
	else if (root->type == PIPE)
		execute_pipe(root, env);
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
	(*fd)[0][FD_READ] = STDIN_FILENO;
	(*fd)[process - 1][FD_WRITE] = STDOUT_FILENO;
	*pid = (pid_t *)ft_calloc(sizeof(pid_t), process);
	if (*pid == NULL)
		return (1);
	return (0);
}

int	update_exitcode(int status, t_envp *env) 
// 만약 ?를 언셋한 상태라면? 아니지 unset 할 수 없지 키값에서 걸리니까??아닌가? 언셋도 키값을 보나??
{
	char	*exitcode;
	char	*save;
	
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

void	execute_pipe(t_node *root, t_envp *env)
{
    int **fd;
    pid_t *pid;
    int status;
    int process;
    int temp_fd[2];
    int i;
    t_node *line;

    process = count_process(root);
	if (initial_pipe(process, &fd, &pid))
		return ;
    i = 0;
    while (root->type == PIPE)
    {
        temp_fd[0] = fd[i][FD_WRITE];
        temp_fd[1] = fd[i+1][FD_READ];
        pipe(temp_fd);
        pid[i] = fork();
        if (pid[i] < 0)
		{
			printf("error\n");
			return ;
		}
        else if (pid[i])
        {
            if (i != 0)
				close(fd[i][FD_READ]);
            if (i != process - 1)
				close(fd[i][FD_WRITE]);
            if (root->right)
                root = root->right;
            i += 1;
            if (i == process -1)
            {
                i = 0;
				while (i < process)
				{
					waitpid(pid[i], &status, 0);
					i += 1;
				}
				if (update_exitcode(status, env))
					return ;
            }
        }
        else
        {
            if (i == process -1)
                //마지막 라인이라는 뜻 : root->right에 대해서 진행
            {
                if (root->right->type == LINE)
                {
                    line = root->right;
                    //내부를 함수로 빼면 밑에 root->left와 합치기 가능할지도
                    if (line->left)
                    	check_redirection(line->left, fd[i]);
                    dup2(fd[i - 1][FD_READ], STDIN_FILENO);
                    close(fd[i - 1][FD_READ]);
                    dup2(fd[i][FD_WRITE], STDOUT_FILENO);
                    if (line->right)
                        execute(line, env);
                }
            }
            if (root->left->type == LINE)
            {
                line = root->left;
                if (line->left)
                    check_redirection(line->left, fd[i]);
                if (i != 0)
                {
                    dup2(fd[i - 1][FD_READ], STDIN_FILENO);
                    close(fd[i - 1][FD_READ]);
                }
                dup2(fd[i][FD_WRITE], STDOUT_FILENO);
                close(fd[i][FD_WRITE]);
                close(fd[i + 1][FD_READ]);
                close(fd[process -1][FD_WRITE]);
                if (line->right)
                    execute(line, env);
            }
        }
    }
}

int run_builtin(t_node *command, t_envp *env)
{
	if (ft_strequal("pwd", command->str) || ft_strequal("PWD", command->str))
		return (builtin_pwd());
	if (ft_strequal("cd", command->str))
		return (builtin_cd(command, env));
	if (ft_strequal("exit", command->str))
		return (builtin_exit(command, env));
	if (ft_strequal("env", command->str) || ft_strequal("ENV", command->str))
		return (builtin_env(env));
	if (ft_strequal("export", command->str))
		return (builtin_export(command->right, env)); // 얘만 command->right
	if (ft_strequal("echo", command->str) || ft_strequal("ECHO", command->str))
		return (builtin_echo(command));
	if (ft_strequal("unset", command->str))
		return (builtin_unset(command, env));
	if (check_equal(command->str))
	{
		if (check_invalid(command->str) == 2)
			return (add_to_env_plus(command->str, env, SHOW));
		else if (check_invalid(command->str) == 0)
			return (add_to_env(command->str, env, HIDE));
	}
	return (0);
}

void    execute_line(t_node *line, t_envp *env)
{
    int save_fd[2];
	int	fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
    if (check_builtin(line->right))
    {
        save_fd[0] = dup(STDIN_FILENO);
        save_fd[1] = dup(STDOUT_FILENO);
        if (line->left)
            check_redirection(line->left, fd);
        if (line->right)
        run_builtin(line->right, env);
        dup2(save_fd[0], STDIN_FILENO);
        dup2(save_fd[1], STDOUT_FILENO);
        close(save_fd[0]);
        close(save_fd[1]);
		//빌트인 정상실행시 -> exitcode update필요
    }
    else
    {
        pid_t pid;
        int status;
        pid = fork();
        if(pid)
        {
            waitpid(pid, &status, 0);
            update_exitcode(status, env);
        }
        else
        {
            if (line->left)
                check_redirection(line->left, fd);
            if (line->right)
                execute(line->right, env);
        }
    }
}
