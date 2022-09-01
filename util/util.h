/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:50:37 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/01 16:32:52 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "../define.h"
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>

//builtin_util.c
int		change_env_value(char *str, int display, t_envp *env);
int		change_env_value_plus(char *str, int display, t_envp *env);
int		add_to_env(char *str, int display);
int		add_to_env_plus(char *str, int display);
int		append_envp(t_envp *env, t_envp *prev, char *str, int display);

//libft_util.c
int		ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
int		ft_strequal(char *s1, char *s2);

//libft_util2.c
char	*ft_itoa(int n);
int		ft_isnum(char *str);
int		ft_atoi(const char *str);

//libft_util3.c
int		check_equal(char *str);
int		check_invalid(char *str);
int		max(int len1, int len2);
int		free_both(char *s1, char *s2);

//split_util.c
char	**ft_split(char const *s, char c);

//parse_util.c
char	*ft_strdup_idx(int i, int j, char *str);
char	*ft_strjoin(char *s1, char *s2, int flag);
char	find_quotes(char *str, int *first, int *second);

//prase_util2.c
int		check_valid(int i, int j, char *str);
void	free_tokenlist(t_token *tokenlist);
void	signal_exit_code(char *exitcode);

//pipe_util.c
char	*find_path(char **env_path, char *command);
char	**get_path(void);
char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3);

//pipe_util2.c
int		ft_free(char *str);
void	free_double_array(char **string);
void	print_error(char *str1, char *str2, char *str3, char *str4);

//pipe_util3.c
int		check_builtin(t_node *command);
int		run_builtin(t_node *command, t_node *ast, t_token *token);
int		count_process(t_node *root);
char	**make_command_array(t_node *command);
int		get_command_size(t_node *command);

//pipe_util4.c
void	ft_dup2(int fd1, int fd2);
int		ft_close(int fd);
int		update_exitcode(int status);

//envp_util.h
t_envp	*make_new_envp(char *str, int display);
char	*envp_split_key(char *str);
char	*envp_split_val(char *str);
t_envp	*arrange_envp(char **envp);

//envp_util2.h
char	**dearrange_envp(void);
int		get_env_size(t_envp *head);
t_envp	*free_envp(t_envp *head);

//ast_util.h
t_node	*make_new_node(char *str, int type, t_node *papa);
t_node	*make_root_node(int i);
int		syntax_check_pipe(t_token *token, t_node *head);
int		syntax_check_redirect(t_token *token);
void	free_tree(t_node *head);

#endif
