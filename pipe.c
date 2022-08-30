/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:08 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 00:21:16 by heeskim          ###   ########.fr       */
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

void	execute_pipe(t_node *root, t_node *ast, t_token *token)
{
	int		fd[2];
	int		fd2[2];
	int		temp[2];
	int		save[2];
	t_node *line;
	pid_t	pid1;
	pid_t	pid2;

	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	pipe(temp);
	fd[0] = STDIN_FILENO;
	fd[1] = temp[0];
	fd2[0] = temp[1];
	fd2[1] = STDOUT_FILENO;
	
	pid1 = fork();
	if (pid1 == -1)
		ft_error();
	else if (pid1 == 0)
	{
		line = root->left;
		check_redirection(line->left, fd);
		if (line->right)
		{
			if (check_builtin(line->right))
				run_builtin(line->right, ast, token);
			else
				execute(line->right);
		}
		dup2(save[0], STDIN_FILENO);
		dup2(save[1], STDOUT_FILENO);
		close(save[0]);
		close(save[1]);
	}
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_error();
		else if (pid2 == 0)
		{
			line = root->right;
			check_redirection(line->left, fd2);
			if (line->right)
			{
				if (check_builtin(line->right))
					run_builtin(line->right, ast, token);
				else
					execute(line->right);
			}
			dup2(save[0], STDIN_FILENO);
			dup2(save[1], STDOUT_FILENO);
			close(save[0]);
			close(save[1]);
		}
		else
		{
			dup2(save[0], STDIN_FILENO);
			dup2(save[1], STDOUT_FILENO);
			close(save[0]);
			close(save[1]);
			close(fd[1]);
			close(fd2[0]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
		}
	}
}
	
void    execute_line(t_node *line, t_node *ast, t_token *token)
{
    int save_fd[2];
	int	fd[2];
    pid_t pid;
    int status;

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
    save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
    if (check_builtin(line->right))
    {
        check_redirection(line->left, fd);
        if (line->right)
            run_builtin(line->right, ast, token);
		//빌트인 정상실행시 -> exitcode update필요
    }
    else
    {
        pid = fork();
        if(pid)
        {
            waitpid(pid, &status, 0);
            update_exitcode(status);
        }
        else
        {
            if (line->left)
                check_redirection(line->left, fd);
            if (line->right)
                execute(line->right);
        }
    }
    dup2(save_fd[0], STDIN_FILENO);
    dup2(save_fd[1], STDOUT_FILENO);
    close(save_fd[0]);
    close(save_fd[1]);
}
