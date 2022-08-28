/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:50 by heeskim           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2022/08/28 04:49:43 by sojoo            ###   ########.fr       */
=======
/*   Updated: 2022/08/28 04:35:38 by heeskim          ###   ########.fr       */
>>>>>>> df05211eb4f147ab5b7fc6d01f98abeac76b3d14
=======
/*   Updated: 2022/08/28 15:42:38 by heeskim          ###   ########.fr       */
>>>>>>> d72f3592e6b9d51185d5a56245380c3833ecdb2c
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

	(void) argc;
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
