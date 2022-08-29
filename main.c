/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:50 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/29 22:16:57 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"
// #include "builtin.h"
// #include "pipe.h"

void	print_start_shell(void)
{
	printf("████████████████████████▀▀████████████████████████\n");
	printf("█████████████████████▀▀    ▀▀█████████████████████\n");
	printf("████████████████████          ████████████████████\n");
	printf("███████████████████            ███████████████████\n");
	printf("██████████████████              ██████████████████\n");
	printf("                  ███ KINDER ███                  \n");
	printf("                  ██████████████                  \n");
	printf("                   ████████████     █▀▀▀▀▀▀▀▀▀▀▀▀█\n");
	printf("                    ▀████████▀      █ TEAM - JOY █\n");
	printf("                                    █▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_envp	*env;
	char	*str;

	if (argc != 1)
		exit(1);
	(void) argv;
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
