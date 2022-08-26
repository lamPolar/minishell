/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:35:24 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/26 13:51:53 by heeskim          ###   ########.fr       */
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

t_token *tokenize(char *str)
{
    t_token *res;
    t_token *prev;
    t_token *new;
    int     i;
    int     j;
    char    ch;

    res = make_new_token(-1, NULL);
    prev = res;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ')
        {
            while (str[i] == ' ')
                i++;
        }
        else if (str[i] == '|')
        {
            new = make_new_token(0, ft_strdup_idx(i, i, str));
            prev->next = new;
            prev = prev->next;
            i++;
            continue ;
        }
        else if (str[i] == '>' || str[i] == '<')
        {
            ch = str[i];
            if (str[i + 1] == ch)
                j = i + 1;
            else
                j = i;
            new = make_new_token(1, ft_strdup_idx(i, j, str));
            prev->next = new;
            prev = prev->next;
            i = j + 1;
            continue ;
        }
        else
        {
            j = find_word(str, i);
            new = make_new_token(2, ft_strdup_idx(i, j - 1, str));
            prev->next = new;
            prev = prev->next;
            i = j;
            continue ;
        }
    }
    prev = res;
    res = res->next;
    free(prev);
    return (res);
}

char    *ft_strdup_idx(int i, int j, char *str)
{
    char    *res;
    int     idx;

    res = (char *)ft_calloc(sizeof(char), (j - i + 2));
    if (res == NULL)
        return (NULL);
    idx = 0;
    while (i <= j)
    {
        res[idx] = str[i];
        idx += 1;
        i += 1;
    }
    res[idx] = '\0';
    return (res);
}

void    execute_str(char *str, t_envp *env)
{
    t_token *tokenlist;

    tokenlist = tokenize(str);
    if (tokenlist == NULL)
        return ;

    int i = 0;
    while (tokenlist != NULL)
    {
        printf("value:%s\ntype:%d\n\n", tokenlist->value, tokenlist->type);
        tokenlist = tokenlist->next;
    }
}