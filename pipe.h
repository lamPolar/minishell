/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/27 22:37:34 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "define.h"
# include "util/util.h"
# include "builtin/builtin.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> 
//# include <sys/stat.h>

//pipe.c
int		count_process(t_node *root);
int		run_pipe(t_node *root, t_envp *env);
void	execute(t_node *command, t_envp *env);
int		execute_function(t_node *command, t_envp *env);
char	**make_command_array(t_node *command);
void	ft_command(t_node *line, t_envp *env);

//redirection
int		check_redirection(t_node *re, int fd[2]);
void	here_doc(int fd, char *delimiter);
void	open_redirection_file(t_node *file, int MODE, int *fd);

#endif
