/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/02 16:54:10 by heeskim          ###   ########.fr       */
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
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

//pipe.c
int		initial_pipe(int process, int **pipes, pid_t **pid, t_node **line);
void	close_pipe(int process, int *pipes);
t_node	*child_process(int *pipes, int i, int process, t_node *root);
void	parent_process(int *pipes, pid_t *pid, int i, int process);
void	check_fd_error(int fd[2], int flag);

//redirect.c
int		check_redirection(t_node *re, int *infd, int *outfd);
void	here_doc(int *fd, char *delimiter);
void	check_here_doc(int *infd, char *delimiter);
int		check_infile(t_node *re, int *infd);
int		check_outfile(t_node *re, int *outfd);

//execute.c
void	execute_tree(t_node *root, t_node *ast, t_token *token);
void	execute_pipe(t_node *root, t_node *ast, t_token *token, int process);
void	execute_line(t_node *line, t_node *ast, t_token *token);
void	execute_builtin(t_node *line, t_node *ast, t_token *token);

//execute2.c
void	execute_function(t_node *line, t_node *ast, t_token *token);
void	execute(t_node *command);

//signal.c
void	signal_handler(int signum);
void	c_handler(int pid);
void	q_handler(int pid);
void	sigint_inpipe(int signum);
void	signal_heredoc(int signum);

#endif
