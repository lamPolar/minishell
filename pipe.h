/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/26 13:15:51 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "parse.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> 
# include <sys/stat.h>

//mode 순서 : << < > >>
#define HEREDOC 0
#define INFILE 1
#define OUTFILE 2
#define APPEND_OUT 3

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
void	ft_error(void);
void	ft_free(char *str);
void	free_double_array(char **string);
char	*find_path(char *env_path, char *command);
char	**get_path(char **environ);
void	ft_first_command(int *fd, char *argv[], char *envp[]);
int		run_pipe(int process, char **command[], t_envp *env);
void	execute(t_node *command, t_envp * env);
void	ft_command(int *fd, t_node *command, t_envp *env);

#endif
