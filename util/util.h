/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:50:37 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 04:18:58 by heeskim          ###   ########.fr       */
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
# include <readline/readline.h>

//builtin_util.c
int		ft_strequal(char *s1, char *s2);
int		check_equal(char *str);
int		check_invalid(char *str);
int		ft_isnum(char *str);
int		max(int len1, int len2);
int		ft_atoi(const char *str);
int		free_both(char *s1, char *s2);
int		change_env_value(char *str, t_envp *env, int display);
int		add_to_env(char *str, t_envp *env, int display);
int		change_env_value_plus(char *str, t_envp *env, int display);
int		add_to_env_plus(char *str, t_envp *env, int display);



//libft_util.c
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

//parse_util.c
char	*ft_strdup_idx(int i, int j, char *str);
char	*ft_strjoin(char *s1, char *s2, int flag);
char	find_quotes(char *str, int *first, int *second);
int		check_valid(int i, int j, char *str);

//pipe_util.c
char	*find_path(char **env_path, char *command);
char	**get_path(t_envp *env);
char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
void	ft_error(void);
void	ft_free(char *str);
void	free_double_array(char **string);

//envp_util.h
t_envp	*make_new_envp(char *str, int display);
char	*envp_split_key(char *str);
char	*envp_split_val(char *str);
t_envp	*free_envp(t_envp *head);
char	**dearrange_envp(t_envp *env);
int		get_env_size(t_envp *env);
char	*get_env_value(char *key, t_envp *env);

//ast_util.h
t_node	*make_new_node(char *str, int type, t_node *papa);

#endif