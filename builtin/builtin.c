/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:31:56 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 00:07:02 by sojoo            ###   ########.fr       */
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
	}
	else
		numeric_exit(argument->str, ast, token);
	return (0);
}

void	numeric_exit(char *str, t_node *ast, t_token *token)
{
	if (ft_isnum(str) == 0)
		print_error("KINDER: exit: ", str, ": numeric argument required", 0);
	free_tree(ast);
	free_tokenlist(token);
	free_envp(g_env);
	if (ft_isnum(str) == 1)
		exit(ft_atoi(str));
	exit(255);
}
