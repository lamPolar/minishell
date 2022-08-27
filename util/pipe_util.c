/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:54:57 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 04:44:45 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

char	*find_path(char **env_path, char *command)
{
	struct stat	buf;
	char		*path;
	int			i;

	if (stat(command, &buf) != -1)
		return (command);
	i = 0;
	while (env_path[i])
	{
		path = ft_strjoin_three(env_path[i], "/", command);
		if (path == NULL)
			return (NULL);
		if (stat(path, &buf) != -1)
			break ;
		ft_free(path);
		i += 1;
	}
	if (env_path[i] == NULL)
	{
		printf("KINDER: %s: command not found\n", command);
		exit(EXIT_FAILURE);
	}
	free_double_array(env_path);
	return (path);
}

char	**get_path(t_envp *env)
{
	char	**path_array;

	while (env && ft_strequal(env->key, "PATH") == 0)
		env = env->next;
	if (env == NULL)
		env = NULL; // 일단 아무거나 써둠
		//path환경변수 없으면? 어떻게 할까?
		//없는채로 넘겨줘라...?
	else
	{
		path_array = ft_split(env->value, ':');
		if (path_array == NULL)
			return (NULL);
		return (path_array);
	}
}

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*new;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	new = (char *)ft_calloc(len1 + len2 + len3 + 1, sizeof(char));
	if (!new)
		return (0);
	ft_strlcat(new, s1, len1 + 1);
	ft_strlcat(new, s2, len1 + len2 + 1);
	ft_strlcat(new, s3, len1 + len2 + len3 + 1);
	return (new);
}

void	ft_error(void)
{
	printf("\e[1;31mError: \e[0m %s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

void	ft_free(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	free_double_array(char **string)
{
	int	i;

	i = 0;
	if (string == NULL)
		return ;
	while (string[i])
	{
		ft_free(string[i]);
		string[i] = NULL;
		i += 1;
	}
	free(string);
	string = NULL;
}
