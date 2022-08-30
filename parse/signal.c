/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 05:16:45 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/30 17:18:10 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void    signal_set(void)
{
    signal(SIGINT, signal_handler); //ctrl+C 처리
    signal(SIGQUIT, signal_handler); //ctrl+\ 처리
}

void    signal_handler(int signum)
{
    int pid;
    int status;

    pid = waitpid(-1, &status, WNOHANG);
    if (signum == SIGINT)
        c_handler(pid);
    else if (signum == SIGQUIT)
        q_handler(pid);
}

void    c_handler(int pid)
{
    if (pid == -1)
	{	
        printf("\n");
		rl_on_new_line(); //새로운 줄을 띄웠다고 생각하고 프롬프트를 띄움
		rl_replace_line("", 0); // 프롬프트에 이미 있던 문자열을 날려줌 (커서이동)
		rl_redisplay(); //replace의 text를 실제로 띄워줌
	}
	else
	{
		printf("^C\n");
	}
}

void    q_handler(int pid)
{
    if (pid == -1)
    {
        rl_on_new_line();
        rl_redisplay();
    }
    else
    {
        printf("^\\Quit: 3\n");
    }
}

// int signal_exit_code(char *exitcode)
// {

// }