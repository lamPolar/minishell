/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:31:56 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/02 03:12:46 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(void)
{
	char	*buf;

	buf = get_env_value("PWD");
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
		return (1);
	}
	else
		numeric_exit(argument->str, ast, token);
	return (0);
}

void	numeric_exit(char *str, t_node *ast, t_token *token)
{
	int		exitcode;
	char	*save;

	if (ft_isnum(str) == 0)
		print_error("KINDER: exit: ", str, ": numeric argument required", 0);
	exitcode = ft_atoi(str);
	save = ft_strdup(str);
	free_tree(ast);
	free_tokenlist(token);
	free_envp(g_env);
	if (ft_isnum(str) == 1)
	{
		check_atoi_error(save, exitcode);
		free(save);
		exit(exitcode);
	}
	exit(255);
}
