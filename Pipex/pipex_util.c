/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:54:57 by heeskim           #+#    #+#             */
/*   Updated: 2022/07/02 13:53:50 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **path_array, char *command)
{
	char	*path;
	int		i;

	if (access(command, F_OK) == 0)
		return (command);
	i = 0;
	while (path_array[i])
	{
		path = ft_strjoin(path_array[i], "/");
		if (path == NULL)
			return (NULL);
		path = ft_strjoin(path, command);
		if (path == NULL)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
		ft_free(path);
		i += 1;
	}
	if (path_array[i] == NULL)
		return (NULL);
	free_everything(path_array);
	return (path);
}

char	**get_path(char **environ)
{
	int		i;
	char	**path_array;

	i = 0;
	while (ft_strnstr(environ[i], "PATH", 4) == 0)
		i += 1;
	path_array = ft_split(environ[i] + 5, ':');
	if (path_array == NULL)
		return (NULL);
	return (path_array);
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

void	free_everything(char **string)
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
