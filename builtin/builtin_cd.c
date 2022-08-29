/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:21:18 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/30 01:39:18 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_home(t_node *command, t_envp *env)
{
	char	*home;
	char	*path;
	char	*save;

	home = get_env_value("HOME", env);
	if (home == NULL)
		return (1);
	if (ft_strequal(command->str, "~") || ft_strequal(command->str, "--"))
	{
		command->str = home;
		return (0);
	}
	else if (command->str[0] == '~' && command->str[1] == '/')
	{
		path = ft_strjoin(home, &(command->str[1]), 0);
		if (path == NULL)
			return (1);
		free(home);
		save = command->str;
		command->str = path;
		free(save);
		return (0);
	}
	free(home);
	return (0);
}

int	check_oldpwd(t_node *command, t_envp *env)
{
	char	*oldpwd;
	char	*save;

	oldpwd = get_env_value("OLDPWD", env);
	if (oldpwd == NULL)
		return (1);
	if (ft_strequal(command->str, "-"))
	{
		save = command->str;
		command->str = oldpwd;
		free(save);
		return (0);
	}
	free(oldpwd);
	return (0);
}

char	*make_pwd(char *str, char **pwd)
{
	char	*temp;
	char	*oldpwd;
	char	*save;
	size_t	size;

	save = *pwd;
	*pwd = ft_strjoin("PWD=", str, 0);
	free(save);
	temp = NULL;
	size = 0;
	temp = getcwd(temp, size);
	if (temp == NULL)
		return (NULL);
	oldpwd = ft_strjoin("OLDPWD=", temp, 0);
	free(temp);
	return (oldpwd);
}

int	change_pwd(char *oldpwd, char *pwd, t_envp *env)
{
	int	flag;

	flag = 0;
	if (add_to_env(oldpwd, env, SHOW))
		flag = 1;
	if (add_to_env(pwd, env, SHOW))
		flag = 1;
	free_both(pwd, oldpwd);
	if (flag)
		return (1);
	return (0);
}

int	builtin_cd(t_node *command, t_envp *env)
{
	char	*oldpwd;
	char	*pwd;
	t_node	*argument;

	argument = command->right;
	if (argument == NULL)
	{
		argument = make_new_node("~", COMMAND, command);
		if (argument == NULL)
			return (1);
	}
	if (check_home(argument, env) || check_oldpwd(argument, env))
		return (1);
	pwd = (char *)ft_calloc(sizeof(char), 1);
	oldpwd = make_pwd(argument->str, &pwd);
	if (oldpwd == NULL || pwd == NULL)
		return (free_both(pwd, oldpwd));
	if (chdir(argument->str) == -1)
	{
		printf("KINDER: cd: %s: %s\n", argument->str, strerror(errno));
		return (1);
	}
	return (change_pwd(oldpwd, pwd, env));
}
//mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ;
// pwd ; cd . ; pwd ; cd .. ; pwd