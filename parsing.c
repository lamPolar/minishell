#include <stdio.h>
#include <stdlib.h>

typedef struct envp
{
    char        *key;
    char        *value;
    struct envp *next;
}   t_envp;

typedef struct token
{
    int     type;
    char    *value;
}   t_token;

int count_token(char *str)
{
    int     cnt;
    int     i;
    char    ch;

    cnt = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ')
        {
            while (str[i] == ' ')
                i++;
        }
        else if (str[i] == '>' || str[i] == '<')
        {
            ch = str[i];
            i++;
            if (str[i] == ch)
                i++;
            cnt++;
            continue ;
        }
        else if (str[i] == '|')
        {
            cnt++;
            i++;
            continue ;
        }
        else
        {
            while (str[i] != ' ' && str[i] != '\0' && str[i] != '|' && str[i] != '>' && str[i] != '<')
                i++;
            cnt++;
        }
    }
    return (cnt);
}

int find_ch(char *str, int i, char ch)
{
    i++;
    while (str[i] != '\0')
    {
        if (str[i] == ch)
            return (i);
        i++; 
    }
    return (0);
}

int find_word(char *str, int i)
{
    i++;
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '|' && str[i] != '>' \
        && str[i] != '<')
        i++;
    return (i);
}

char    *ft_strdup_idx(int i, int j, char *str)
{
    char    *res;
    int     idx;

    res = (char *)malloc(sizeof(char) * (j - i + 2));
    if (!res)
        return (0);
    idx = 0;
    while (i <= j)
    {
        res[idx] = str[i];
        idx++;
        i++;
    }
    res[idx] = '\0';
    return (res);
}

void    fill_token(t_token *list, char *str)
{
    int     i;
    int     j;
    int     idx;
    char    ch;

    i = 0;
    j = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ')
        {
            while (str[i] == ' ')
                i++;
        }
        else if (str[i] == '>' || str[i] == '<')
        {
            ch = str[i];
            idx = find_ch(str, i, ch);
            if (idx == 0)
                idx = i;
            list[j].value = ft_strdup_idx(i, idx, str);
            list[j].type = 1;
            i = idx + 1;
            j++;
            continue ;
        }
        else if (str[i] == '|')
        {
            list[j].value = ft_strdup_idx(i, i, str);
            list[j].type = 0;
            i++;
            j++;
            continue ;
        }
        else
        {
            idx = find_word(str, i);
            list[j].value = ft_strdup_idx(i, idx - 1, str);
            list[j].type = 2;
            i = idx;
            j++;
        }
    }
    list[j].value = 0;
    list[j].type = -1;
}

t_token *tokenize(char *str)
{
    t_token *res;
    int     size;

    size = count_token(str);
    res = (t_token *)malloc(sizeof(t_token) * (size + 1));
    if (!res)
        return (0);
    fill_token(res, str);

    return (res);
}

int execute_str(char *str, t_envp *env)
{
    t_token *tokenlist;

    tokenlist = tokenize(str);
    
    int i = 0;
    while (tokenlist[i].type != -1)
    {
        printf("value:%s\ntype:%d\n\n", tokenlist[i].value, tokenlist[i].type);
        i++;
    }

    return (0);
}