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
        if (str[i] == '\"' || str[i] == '\'')
        {
            ch = str[i];
            i++;
            while (str[i] != ch)
                i++;
            cnt++;
            i++;
            continue ;
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
            while (str[i] != ' ' && str[i] != '\0' && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '\"' && str[i] != '\'')
                i++;
            cnt++;
        }
    }
    return (cnt);
}

void    fill_token(t_token *list)
{
    
}

t_token *tokenize(char *str)
{
    t_token *res;
    int     size;

    size = count_token(str);
    res = (t_token *)malloc(sizeof(t_token) * (size + 1));
    if (!res)
        return (0);
    fill_token(res);

    return (res);
}

int execute_str(char *str, t_envp *env)
{
    t_token *tokenlist;

    tokenlist = tokenize(str);

    return (0);
}

//공백 문자 관련하여 띄어쓰기만을 처리해야하는지, \t \v 깉은 것도
//생각해야 하는지? bash에서는 \t 입력시 t만 출력되고 있음
//bash와 같게 표현해야 하는가? \는 요구사항에서 나온 문자가 아니므로
//처리해야하지 않는건가? 라는....... 궁금증.....
//그리고 지금은 >>와 <<만 가능하게 잘랐는데 >>>나 <>(이거 된대여)는 어떻게 처리할 건지?