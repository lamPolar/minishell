/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:54:57 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/22 22:09:43 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*find_path(char *env_path, char *command)
{
	char	**path_array;
	char	*path;
	int		i;

	if (access(command, F_OK) == 0)
		return (command);
	path_array = ft_split(env_path, ':');
	if (path_array == NULL)
		ft_error();
	i = 0;
	while (path_array[i])
	{
		path = ft_strjoin_three(path_array[i], "/", command);
		if (path == NULL)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
		ft_free(path);
		i += 1;
	}
	if (path_array[i] == NULL)
		return (NULL);
	free_double_array(path_array);
	return (path);
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
	perror("\e[1;31mError");
	exit(EXIT_FAILURE);
}

void	ft_free(char *str)
{
	free(str);
	str = NULL;
}

void	free_double_array(char **string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		ft_free(string[i]);
		i += 1;
	}
	free(string);
	string = NULL;
}
