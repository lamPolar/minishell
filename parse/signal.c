/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 05:16:45 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/28 12:37:06 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// void    signal_set(void)
// {
//     signal(SIGINT, signal_handler); //ctrl+C 처리
//     signal(SIGQUIT, signal_handler); //ctrl+\ 처리
// }

// void    signal_handler(int signum)
// {
//     int pid;
//     int status;

//     pid = waitpid(-1, &status, WNOHANG);
//     if (signum == SIGINT)
//         c_handler(pid);
//     else if (signum == SIGQUIT)
//         q_handler(pid);
// }

// void    c_handler(int pid)
// {
//     if (pid == -1)
// 	{	
// 		rl_on_new_line();
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else
// 	{
// 		printf("^C\n");
// 	}
// }

// void    q_handler(int pid)
// {
//     rl_on_new_line();
// }