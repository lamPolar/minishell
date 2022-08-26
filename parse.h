/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:03:58 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/26 17:40:05 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define HIDE 0
# define SHOW 1

typedef struct envp
{
	char		*key;
	char		*value;
	int			display;
	struct envp	*next;
}	t_envp;

typedef struct token
{
	int				type;
	char			*value;
	struct token	*next;
}	t_token;

// typedef struct node
// {
// 	t_node  *left;
// 	t_node  *right;
// 	t_node  *papa;
// 	char    *str;
// 	char    *type;
// }   t_node;

t_envp	*make_new_envp(char *str);
char	*envp_split_val(char *str);
char	*envp_split_key(char *str);
t_envp	*arrange_envp(char **envp);
t_envp	*free_envp(t_envp *head);

int		find_word(char *str, int i);
char	*ft_strdup_idx(int i, int j, char *str);
t_token	*make_new_token(int type, char *value);
t_token	*tokenize(char *str);

void	execute_str(char *str, t_envp *env);

void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	find_quotes(char *str, int *first, int *second);
int check_valid(int i, int j, char *str);
int ft_strequal(char *s1, char *s2);

void    after_tokenize(t_token *tokenlist, t_envp *env);
int delete_quotes(t_token *token, int idx1, int idx2, char ch);
int change_dollar(t_token *tokenlist, t_envp *env);
int find_double_quotes(t_token *tokenlist, t_envp *env, int i);
void    envp_in_value(t_token *tokenlist, t_envp *env, int i, int j);

#endif