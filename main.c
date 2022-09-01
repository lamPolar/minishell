/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:50 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/02 03:56:02 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/parse.h"
#include "execute/pipe.h"

void	print_start_shell(void)
{
	printf("\e[1;94m");
	printf("████████████████████████▀▀████████████████████████\n");
	printf("█████████████████████▀▀    ▀▀█████████████████████\n");
	printf("████████████████████          ████████████████████\n");
	printf("███████████████████            ███████████████████\n");
	printf("██████████████████              ██████████████████\n");
	printf("\e[0;95m");
	printf("                  ███ \e[0;37mKINDER\e[0;95m ███                  \n");
	printf("                  ██████████████                  \n");
	printf("                   ████████████    \e[1;37m █▀▀▀▀▀▀▀▀▀▀▀▀█\n");
	printf("\e[0;95m");
	printf("                    ▀████████▀     \e[1;37m █ TEAM - JOY █\n");
	printf("                                    █▄▄▄▄▄▄▄▄▄▄▄▄█\n\n");
	printf("\e[0m");
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
		str = readline("\e[0;91mKINDER🥚 > \e[0m");
		if (str == NULL)
		{
			write(1, "\x1b[1A", ft_strlen("\x1b[1A"));
			write(1, "\033[11C", ft_strlen("\033[11C"));
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
