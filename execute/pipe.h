/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 15:25:18 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "../define.h"
# include "../util/util.h"
# include "../builtin/builtin.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> 
//# include <sys/stat.h>

//pipe.c
int		initial_pipe(int process, int **pipes, pid_t **pid);
void	close_pipe(int process, int *pipes);
t_node	*child_process(int *pipes, int i, int process, t_node *root);
void	parent_process(int *pipes, pid_t *pid, int i, int process);

//redirect.c
int		check_redirection(t_node *re, int fd[2]);
void	here_doc(int fd, char *delimiter);
int		open_redirection_file(t_node *file, int MODE, int fd);
int		check_infile(t_node *re, int fd);
int		check_outfile(t_node *re, int fd);

//execute.c
void	execute_tree(t_node *root, t_node *ast, t_token *token);
void	execute_pipe(t_node *root, t_node *ast, t_token *token);
void	execute_line(t_node *line, t_node *ast, t_token *token);
void	execute_function(t_node *line, t_node *ast, t_token *token);
void	execute(t_node *command);

#endif
