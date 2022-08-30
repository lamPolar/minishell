/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 04:58:28 by heeskim          ###   ########.fr       */
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
void	execute_tree(t_node *root, t_node *ast, t_token *token);
//void	make_process(t_node *line);
//int		run_pipe(t_node *root);
//void	ft_command(t_node *line);
void	execute_pipe(t_node *root, t_node *ast, t_token *token);
int		update_exitcode(int status);
void    execute_line(t_node *line, t_node *ast, t_token *token);
int     run_builtin(t_node *command, t_node *ast, t_token *token);

//pipe_util2.c
//void	print_node(t_node *root)
int     check_builtin(t_node *command);
int		count_process(t_node *root);
char	**make_command_array(t_node *command);
int		get_command_size(t_node *command);

//redirect.c
int		check_redirection(t_node *re, int fd[2]);
void	here_doc(int fd, char *delimiter);
int		open_redirection_file(t_node *file, int MODE, int fd);
int check_infile(t_node *re, int fd);
int check_outfile(t_node *re, int fd);

//execute.c
void	execute(t_node *command);

#endif
