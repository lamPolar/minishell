/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/22 22:29:57 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h" 

#define REDIRECTION 3

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
void	execute(t_node *command, char **environ);
void	ft_error(void);
void	ft_free(char *str);
void	free_double_array(char **string);
char	*find_path(char *env_path, char *command);
char	**get_path(char **environ);
void	ft_first_command(int *fd, char *argv[], char *envp[]);
void	ft_second_command(int *fd, char *argv[], char *envp[]);

#endif
