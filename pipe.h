/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:25:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/26 21:50:12 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "define.h"
# include "builtin/builtin.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> 
# include <sys/stat.h>

//pipe_util.c
char	*find_path(char **env_path, char *command);
char	**get_path(t_envp *env);
char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
void	ft_error(void);
void	ft_free(char *str);
void	free_double_array(char **string);

//pipe.c
int	    count_process(t_node *root);
int     run_pipe(t_node *root, t_envp *env);
void	execute(t_node *command, t_envp *env);
int	    execute_function(t_node *command, t_envp *env);
int	    get_env_size(t_envp *env);
char	**dearrange_envp(t_envp *env);
char	**make_command_array(t_node *command);
void	ft_command(t_node *line, t_envp *env);

//redirection
void	check_redirection(t_node *re, int fd[2]);
void	here_doc(int fd, char *delimiter);
int 	open_redirection_file(t_node *file, int MODE, int *fd);

//libft_util
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
//int	    ft_atoi(const char *str); //-2147483648 확인
char	**ft_split(char const *s, char c);

#endif
