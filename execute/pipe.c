/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 14:49:41 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	execute_tree(t_node *root, t_node *ast, t_token *token)
{
	if (root->type == LINE)
		execute_line(root, ast, token);
	else if (root->type == PIPE)
        execute_pipe(root, ast, token);
	else
		print_error("KINDER: Wrong AST", 0, 0, 0);
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

void	ft_close(int fd)
{
	int	result;

	if (fd > 2)
		result = close(fd);
    else
        return ;
	if (result == -1)
		print_error("KINDER: close failed", 0, 0, 0);
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
		print_error("KINDER: dup2 failed", 0, 0, 0);
	return (result);
}

void clean_pipe(int process, int *pipes)
{
    int j;

    j = 0;
    while (j < process -1)
    {
        close(pipes[j * 2]);
        close(pipes[(j * 2) + 1]);
        j += 1;
    }
}

void execute_l(t_node *line, t_node *ast, t_token *token)
{
    if (check_builtin(line->right))
    {
        run_builtin(line->right, ast, token);
        exit(0);
    }
    else
    {
        if (line->right)
            execute(line->right);
    }
}

void    parent_process(int *pipes, pid_t *pid, int i, int process)
{
    int status;
    
    if (i == process - 1)
    {
        clean_pipe(process, pipes);
        int j = 0;
        while (j < process)
        {
            if (waitpid(pid[j], &status, 0) == pid[j])
                update_exitcode(status);
            j += 1;
        }
    }
}

t_node *child_process(int *pipes, int i, int process, t_node *root)
{
    t_node  *line;
    int     fd[2];
    
    line = NULL;
    fd[0] = STDIN_FILENO;
    fd[1] = STDOUT_FILENO;
    if (i != 0)
        fd[0] = pipes[(i - 1) * 2];
    if (i != process - 1)
    {
        fd[1] = pipes[(i * 2) + 1];
    }
    //check_redirection(line->left, fd); 
    if (i != process -1)
    {
        line =root->left;
    }
    else if (i == process - 1)
    {
        line = root;
    }
    ft_dup2(fd[0], 0);
    ft_dup2(fd[1], 1);
    return (line);
}

int	initial_pipe(int process, int **pipes, pid_t **pid)
{
	int i;

	*pipes = (int *)ft_calloc(sizeof(pid_t), (process - 1) * 2);
    if (*pipes == NULL)
        return (1);
	i = 0;
    while (i < process - 1)
    {
        pipe((*pipes) + (i * 2));
        i += 1;
    }
	*pid = (pid_t *)ft_calloc(sizeof(pid_t), process);
	if (*pid == NULL)
		return (1);
	return (0);
}

void    execute_pipe(t_node *root, t_node *ast, t_token *token)
{
    int     i;
    t_node  *line;
    int     *pipes;
    pid_t   *pid;
    int     process;
    
    line = NULL;
    process = count_process(root);
    if (initial_pipe(process, &pipes, &pid))
        return ;
    i = 0;
    while (i < process)
    {
        pid[i] = fork();
        if (pid[i] == 0)
        {
            line = child_process(pipes, i, process, root);
            clean_pipe(process, pipes);
            execute_l(line, ast, token);
        }
        else
        {
            parent_process(pipes, pid, i, process);
            if (root->right)
                root = root->right;
            i += 1;
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
        //check_redirection(line->left, fd);
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
            if (waitpid(pid, &status, 0) == pid)
				update_exitcode(status);
        }
        else
        {
            fd[0] = STDIN_FILENO;
            fd[1] = STDOUT_FILENO;
            //fd[0] = check_infile(line->left, STDIN_FILENO);
            //fd[1] = check_outfile(line->right, STDOUT_FILENO);
            // check_redirection(line->left, fd);
			ft_dup2(fd[0], STDIN_FILENO);
            ft_dup2(fd[1], STDOUT_FILENO);
            if (line->right)
			{
                execute(line->right);
			}
        }
    }
}
