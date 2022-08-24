/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:50 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/24 15:39:59 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
// #include "builtin.h"
// #include "pipe.h"

void print_start_shell(void)
{
	printf("sojoo ====================================== and\n");
	printf("====================    ========================\n");
	printf("==================        ======================\n");
	printf("=================          =====================\n");
	printf("================            ====================\n");
	printf("===============              ===================\n");
	printf("===============    KINDER    ===================\n");
	printf("===============              ===================\n");
	printf("================            ====================\n");
	printf("=================          =====================\n");
	printf("heeskim's ============================ minishell\n\n");
}

int main(int arc, char *argv[], char *envp[])
{
    t_envp  *env;
    char    *str;

	print_start_shell();
    env = arrange_envp(envp);
    if (env == NULL)
        return (1);
    while (1)
    {
        str = readline("KINDER🥚 > ");
        if (str == NULL)
            break ;
        add_history(str);
        execute_str(str, env);
        free(str);
    }
    free_envp(env);
    return (0);
}
