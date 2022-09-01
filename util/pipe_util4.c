/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:19:01 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/01 14:28:42 by heeskim          ###   ########.fr       */
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
	char	*save;
	t_envp	*env;

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
		return (0);
	}
	return (1);
}
