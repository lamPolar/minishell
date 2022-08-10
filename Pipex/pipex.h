/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/07/02 13:54:58 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h" 

void	execute(char *argv, char **environ);
void	ft_error(void);
void	ft_free(char *str);
void	free_everything(char **string);
char	*find_path(char **path_array, char *command);
char	**get_path(char **environ);
void	ft_first_command(int *fd, char *argv[], char *envp[]);
void	ft_second_command(int *fd, char *argv[], char *envp[]);

#endif
