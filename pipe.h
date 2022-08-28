/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 09:08:48 by heeskim          ###   ########.fr       */
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
void	execute_tree(t_node *root, t_envp *env);
void	make_process(t_node *line, t_envp *env);
int		count_process(t_node *root);
int		get_command_size(t_node *command);
char	**make_command_array(t_node *command);
//int		run_pipe(t_node *root, t_envp *env);
//void	ft_command(t_node *line, t_envp *env);
void	execute_pipe(t_node *root, t_envp *env);
void	execute_tree(t_node *root, t_envp *env);

//redirect.c
int		check_redirection(t_node *re, int fd[2]);
void	here_doc(int fd, char *delimiter);
void	open_redirection_file(t_node *file, int MODE, int *fd);

//execute.c
int		execute_function(t_node *command, t_envp *env, int fork);
void	execute_process(t_node *command, t_envp *env);
void	execute_with_fork(t_node *command, t_envp *env);

#endif
