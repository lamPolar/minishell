/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:03:58 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/24 17:20:06 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HIDE 0
#define SHOW 1

typedef struct envp
{
    char        *key;
    char        *value;
    struct envp *next;
    int         display;
}   t_envp;

typedef struct token
{
    int             type;
    char            *value;
    struct token    *next;
}   t_token;

typedef struct node
{
    t_node  *left;
    t_node  *right;
    t_node  *papa;
    char    *str;
    char    *type;
}   t_node;

t_envp  *make_new_envp(char *str);
char    *envp_split_val(char *str);
char    *envp_split_key(char *str);
t_envp  *arrange_envp(char **envp);
t_envp  *free_envp(t_envp *head);

int find_word(char *str, int i);
char    *ft_strdup_idx(int i, int j, char *str);
t_token *make_new_token(int type, char *value);
t_token *tokenize(char *str);

void    execute_str(char *str, t_envp *env);

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);

#endif