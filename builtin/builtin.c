/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:31:56 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/30 22:01:33 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(void)
{
	char	*buf;
	size_t	size;

	buf = NULL;
	size = 0;
	buf = getcwd(buf, size);
	if (buf == NULL)
	{
		print_error("KINDER: pwd: ", strerror(errno), 0, 0);
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

int	builtin_exit(t_node *command, t_node *ast, t_token *token)
{
	t_node	*argument;

	printf("🥚 KINDER JOY SHELL EXIT 🥚\n");
	argument = command->right;
	if (argument == NULL)
	{
		free_tree(ast);
		free_tokenlist(token);
		free_envp(g_env);
		exit(0);
	}
	if (argument->right != NULL)
	{
		print_error("KINDER: exit: too many arguments", 0, 0, 0);
		signal_exit_code(ft_strdup("1"));
		return (0);
	}
	else
	{
		if (ft_isnum(argument->str))
			exit(ft_atoi(argument->str));
		print_error("KINDER: exit: ", argument->str, \
			": numeric argument required", 0);
		free_tree(ast);
		free_tokenlist(token);
		free_envp(g_env);
		exit(255);
	}
}
