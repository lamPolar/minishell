/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 05:16:45 by sojoo             #+#    #+#             */
/*   Updated: 2022/09/02 17:51:57 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	signal_handler(int signum)
{
	int	pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
		c_handler(pid);
	else if (signum == SIGQUIT)
		q_handler(pid);
}

void	c_handler(int pid)
{
	if (pid == -1)
	{	
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signal_exit_code(ft_strdup("1"));
	}
	else
	{
		printf("\n");
		signal_exit_code(ft_strdup("130"));
	}
}

void	q_handler(int pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		printf("Quit: 3\n");
		signal_exit_code(ft_strdup("131"));
	}
}

void	signal_inpipe(int signum)
{
	int	pid;
	int	status;

	(void)signum;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{	
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signal_exit_code(ft_strdup("1"));
	}
	else
	{
		if (signum == SIGINT)
			printf("\n");
		signal_exit_code(ft_strdup("0"));
	}
}

void	signal_heredoc(int signum)
{
	int	pid;
	int	status;

	(void)signum;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == -1)
	{
		if (signum == SIGINT)
		{
			printf("\n");
			exit(1);
		}
		else if (signum == SIGQUIT)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else
	{
		if (signum == SIGINT)
			exit(1);
	}
}
