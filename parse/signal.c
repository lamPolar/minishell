/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 05:16:45 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/30 21:58:33 by sojoo            ###   ########.fr       */
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
		rl_on_new_line(); //새로운 줄을 띄웠다고 알림 (실제로 뉴라인이 생기는것이 아니므로 개행 후 사용)
		rl_replace_line("", 0); // 프롬프트에 사용자가 적어놓았던 문자열을 담은 rl_line_buffer의 내용을 빈 문자열로 바꿔 줌
		rl_redisplay(); //바뀌거나 그대로인 rl_line_buffer의 내용을 띄워줌
        signal_exit_code(ft_strdup("1"));
	}
	else
	{
		printf("^C\n");
        signal_exit_code(ft_strdup("130"));
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
        signal_exit_code(ft_strdup("131"));
    }
}
