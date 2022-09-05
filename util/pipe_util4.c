/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:19:01 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/05 14:54:29 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	ft_close(int fd)
{
	int	result;

	if (fd > 2)
		result = close(fd);
	else
		return (0);
	if (result == -1)
	{
		print_error("KINDER: close failed", 0, 0, 0);
		return (1);
	}
	return (0);
}

void	ft_dup2(int fd1, int fd2)
{
	int	result;

	result = 0;
	if (fd1 != fd2)
	{
		result = dup2(fd1, fd2);
		if (ft_close(fd1))
			return ;
	}
	if (result < 0)
		print_error("KINDER: dup2 failed", 0, 0, 0);
}

int	update_exitcode(int status)
{
	char	*exitcode;
	t_envp	*env;

	env = g_env;
	if (WIFSIGNALED(status))
	{
		if (SIGINT == WTERMSIG(status))
			exitcode = ft_strdup("130");
		if (SIGQUIT == WTERMSIG(status))
			exitcode = ft_strdup("131");
	}
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		exitcode = ft_itoa(status);
	}
	if (exitcode == NULL)
		return (1);
	signal_exit_code(exitcode);
	return (0);
}

void	print_atoi_error(char *save)
{
	print_error("KINDER: exit: ", save, " numeric argument required", 0);
	free(save);
	exit(255);
}

void	check_atoi_error(char *save, int result)
{
	int	flag;
	int	i;

	if (result == 0)
	{
		i = -1;
		while (save[++i])
		{
			if (save[i] >= '1' && save[i] <= '9')
				print_atoi_error(save);
		}
	}
	if (result == -1)
	{
		i = -1;
		flag = 0;
		while (save[++i])
		{
			if (save[i] == '-')
				flag = 1;
		}
		if (flag == 0)
			print_atoi_error(save);
	}
}
