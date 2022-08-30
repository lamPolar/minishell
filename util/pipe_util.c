/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:54:57 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 00:55:24 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

char	*find_path(char **env_path, char *command)
{
	struct stat	buf;
	char		*path;
	int			i;

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
		if (stat(command, &buf) != -1)
			return (command);
		print_error("KINDER: ", command, ": command not found", 0);
		exit(127);
	}
	free_double_array(env_path);
	return (path);
}

char	**get_path(void)
{
	char	**path_array;
	t_envp	*env;

	env = g_env;
	while (env && ft_strequal(env->key, "PATH") == 0)
		env = env->next;
	if (env == NULL)
		return (NULL);
	else
	{
		path_array = ft_split(env->value, ':');
		if (path_array == NULL)
			return (NULL);
		return (path_array);
	}
	return (NULL);
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
	if (new == NULL)
		return (NULL);
	ft_strlcat(new, s1, len1 + 1);
	ft_strlcat(new, s2, len1 + len2 + 1);
	ft_strlcat(new, s3, len1 + len2 + len3 + 1);
	return (new);
}
