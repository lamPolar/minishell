/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:35:24 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/26 14:12:38 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int find_word(char *str, int i)
{
    i++;
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '|' && str[i] != '>' \
        && str[i] != '<')
        i++;
    return (i);
}

t_token *make_new_token(int type, char *value)
{
    t_token *new;

    new = (t_token *)ft_calloc(sizeof(t_token), 1);
    if (new == NULL)
        return (NULL);
    new->value = value;
    new->type = type;
    new->next = NULL;
    return (new);
}

int tokenize_pipe(int i, char *str, t_token *prev)
{
    t_token *new;

    new = make_new_token(0, ft_strdup_idx(i, i, str));
    prev->next = new;
    prev = prev->next;
    return (i);
}

int tokenize_redirect(int i, char *str, t_token *prev)
{
    char    ch;
    int     j;
    t_token *new;

    ch = str[i];
    if (str[i + 1] == ch)
        j = i + 1;
    else
        j = i;
    new = make_new_token(1, ft_strdup_idx(i, j, str));
    prev->next = new;
    prev = prev->next;
    i = j;
    return (i);
}

int tokenize_word(int i, char *str, t_token *prev)
{
    int     j;
    t_token *new;

    j = find_word(str, i);
    new = make_new_token(2, ft_strdup_idx(i, j - 1, str));
    prev->next = new;
    prev = prev->next;
    i = j - 1;
    return (i);
}

t_token *tokenize(char *str)
{
    t_token *res;
    t_token *prev;
    int     i;

    res = make_new_token(-1, NULL);
    prev = res;
    i = -1;
    while (str[++i] != '\0')
    {
        if (str[i] == ' ')
            continue ;
        else if (str[i] == '|')
        {
            i = tokenize_pipe(i, str, prev);
            continue ;
        }
        else if (str[i] == '>' || str[i] == '<')
        {
            i = tokenize_redirect(i, str, prev);
            continue ;
        }
        else
            i = tokenize_word(i, str, prev);
    }
    return (res);
    //왜??? 왜 prev가 이어지지 않을까요?? 어떻게 해야할까요???
}

void    execute_str(char *str, t_envp *env)
{
    t_token *tokenlist;

    tokenlist = tokenize(str);
    if (tokenlist == NULL)
        return ;
    
    // int i = 0;
    // while (tokenlist != NULL)
    // {
    //     printf("value:%s\ntype:%d\n\n", tokenlist->value, tokenlist->type);
    //     tokenlist = tokenlist->next;
    // }
}
