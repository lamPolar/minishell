/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:21:18 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/01 18:26:33 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_home(char **str, char *home)
{
	char	*save;
	char	*path;

	if (ft_strequal(*str, "~") || ft_strequal(*str, "--"))
	{
		save = *str;
		*str = home;
		ft_free(save);
		return (0);
	}
	else if (ft_strlen(*str) > 1 && str[0][0] == '~' && str[0][1] == '/')
	{
		path = ft_strjoin(home, &(str[0][1]), 0);
		ft_free(home);
		if (path == NULL)
			return (1);
		save = *str;
		*str = path;
		ft_free(save);
		return (0);
	}
	ft_free(home);
	return (0);
}

int	check_oldpwd(char **str)
{
	char	*oldpwd;
	char	*save;

	oldpwd = get_env_value("OLDPWD");
	if (oldpwd == NULL)
		return (1);
	if (ft_strequal(*str, "-"))
	{
		save = *str;
		*str = oldpwd;
		ft_free(save);
		return (0);
	}
	ft_free(oldpwd);
	return (0);
}

int	update_pwd(int flag)
{
	char	*pwd;
	char	*temp;

	temp = (char *)ft_calloc(sizeof(char), 1096);
	if (temp == NULL)
		return (1);
	temp = getcwd(temp, 1096);
	if (temp == NULL)
	{
		pwd = get_env_value("PWD");
		if (pwd == NULL || add_to_env(pwd, SHOW))
			return (ft_free(pwd));
		ft_free(temp);
		ft_free(pwd);
		return (0);
	}
	if (flag)
		pwd = ft_strjoin("OLDPWD=", temp, 0);
	else
		pwd = ft_strjoin("PWD=", temp, 0);
	ft_free(temp);
	if (pwd == NULL || add_to_env(pwd, SHOW))
		return (ft_free(pwd));
	ft_free(pwd);
	return (0);
}

int	builtin_cd(t_node *command)
{
	char	*str;
	char	*home;

	if (command->right == NULL)
		str = ft_strdup("~");
	else
		str = ft_strdup(command->right->str);
	home = get_env_value("HOME");
	if (home == NULL)
		return (ft_free(str));
	if (check_home(&str, home) || check_oldpwd(&str))
		return (ft_free(str));
	if (update_pwd(OLDPWD))
		return (ft_free(str));
	if (chdir(str) == -1)
	{
		print_error("KINDER: cd: ", str, ": ", strerror(errno));
		return (ft_free(str));
	}
	ft_free(str);
	return (update_pwd(PWD));
}
