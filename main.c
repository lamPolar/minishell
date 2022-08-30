/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:50 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/30 16:52:56 by sojoo            ###   ########.fr       */
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
	struct termios	term;

	if (argc != 1)
		exit(1);
	(void) argv;
	print_start_shell();
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal_set();
	env = arrange_envp(envp);
	if (env == NULL)
		return (1);
	while (1)
	{
		str = readline("KINDER🥚 > "); // 디렉토리를 확인?
		if (str == NULL)
		{
			write(1, "\x1b[1A", ft_strlen("\x1b[1A"));
			write(1, "\033[10C", ft_strlen("\033[10C"));
			printf("exit\n");
			break ;
		}
		else if (str[0] != '\0')
			add_history(str);
		execute_str(str, env);
		free(str);
	}
	free_envp(env);
	return (0);
}
