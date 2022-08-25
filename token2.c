/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:35:24 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/24 17:09:04 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//token.c 원본
//후처리 할 것 : $변수 $? 따옴표 삭제

#include "parse.h"

int find_word(char *str, int i)
{
    i++;
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '|' && str[i] != '>' \
        && str[i] != '<' && str[i] != '\'' && str[i] == '\"')
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
    int     j;
    int     i;
    char    ch;

    res = make_new_token(-1, NULL);
    prev = res;
    i = -1;
    while (str[++i] != '\0')
    {
        if (str[i] == ' ')
            continue ;
        else if (str[i] == '\'' || str[i] == '\"')
        {
            ch = str[i];
            j = i + 1;
            while (str[j] != '\0')
            {
                if (str[j] == ch)
                    break ;
                j++;
            }
            if (str[i - 1] != ' ' && prev->type == 2)
                modify_value();
                //일단 따옴표가 닫혔든 열렸든 앞이 문자였으면 무조건 따옴표 친구들 포함해서 prev 토큰을 하나의 문자열로 수정해줘야함
                //그 속에서 열렸으면 다음 인덱스부터 문자가 끝나는 기준 (find_word)에 따라서 자르면 되고
                //닫혔으면 닫는 따옴표 다음 인덱스부터 자르기
            else
                //앞에 문자가 없다는건 새로운 토큰의 시작이 따옴표라는 소리임
                //위랑 똑같이 열렸으면 다음 인덱스부터 문자 기준 자르기, 닫혔으면 닫는 따옴표 다음 인덱스부터 자르기

                //근데 echo hi "my" name 처럼 띄어쓰기로 구분된거는 하나에 토큰에 hi "my" name을 넣을 수 없는데 어카죠?
                //괜찮을깝셔???? echo가 그렇게 작동하나요???
                //그리고 이거 줄 수 어카죠 개큰일남
            continue ;
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
        }
    }
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
