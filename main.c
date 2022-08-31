/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:50 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 17:14:54 by heeskim          ###   ########.fr       */
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

void	first_init(int argc, char *argv[], struct termios *term)
{
	if (argc != 1)
		exit(1);
	(void) argv;
	print_start_shell();
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	signal_set();
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*str;
	struct termios	term;

	first_init(argc, argv, &term);
	g_env = arrange_envp(envp);
	if (g_env == NULL)
		return (1);
	while (1)
	{
		str = readline("KINDER🥚 > "); // 디렉토리를 확인?
		if (str == NULL)
		{
			write(1, "\x1b[1A", ft_strlen("\x1b[1A")); //커서를 윗줄로 이동
			write(1, "\033[11C", ft_strlen("\033[11C")); //커서를 10만큼 뒤로 이동
			printf("exit\n");
			break ;
		}
		else if (str[0] != '\0')
			add_history(str);
		execute_str(str);
		free(str);
	}
	free_envp(g_env);
	return (0);
}
