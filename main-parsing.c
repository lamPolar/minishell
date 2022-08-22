#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct envp
{
    char        *key;
    char        *value;
    struct envp *next;
}   t_envp;

// typedef struct node
// {
//     t_node  *left;
//     t_node  *right;
//     t_node  *papa;
//     char    *str;
//     char    *type;
// }   t_node;

void    free_envp(t_envp *head)
{
    t_envp  *prev;

    while (head != NULL)
    {
        if (head->key)
            free(head->key);
        if (head->value)
            free(head->value);
        prev = head;        
        head = head->next;
        free(prev);
    }
}

char    *envp_split_key(char *str)
{
    char    *res;
    int     i;

    i = 0;
    while (str[i] != '=')
        i++;
    res = (char *)malloc(sizeof(char) * (i + 1));
    if (!res)
        return (0);
    i = 0;
    while (str[i] != '=')
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

char    *envp_split_val(char *str)
{
    char    *res;
    int     i;
    int     j;

    i = 0;
    while (str[i] != '=')
        i++;
    i++;
    j = 0;
    while (str[i + j] != '\0')
        j++;
    res = (char *)malloc(sizeof(char) * (j + 1));
    if (!res)
        return (0);
    j = 0;
    while (str[i] != '\0')
    {
        res[j] = str[i];
        i++;
        j++;
    }
    res[j] = '\0';
    return (res);
}

t_envp  *make_new_node(char *str)
{
    t_envp  *new;

    new = (t_envp *)malloc(sizeof(t_envp));
    if (!new)
        return (0);
    new->key = envp_split_key(str);
    new->value = envp_split_val(str);
    new->next = NULL;
    if (new->key == 0 || new->value == 0)
        return (0);
    return (new);
}

t_envp  *arrange_envp(char **envp)
{
    t_envp  *head;
    t_envp  *prev;
    t_envp  *new;
    int     cnt;

    head = make_new_node(envp[0]);
    if (!head)
    {
        free_envp(head);
        return (0);
    }
    prev = head;
    cnt = 0;
    while (envp[++cnt] != 0)
    {
        new = make_new_node(envp[cnt]);
        if (!new)
        {
            free_envp(head);
            return (0);
        }
        prev->next = new;
        prev = prev->next;
    }
    return (head);
}

int main(int argc, char **argv, char **envp)
{
    t_envp  *env;
    char    *str;

    env = arrange_envp(envp);
    if (!env)
        return (0);
    // while (1)
    // {
    //     str = readline("> ");
    //     if (!str)
    //         break ;
    //     add_history(str);
    //     free(str);
    // }
    return (0);
}