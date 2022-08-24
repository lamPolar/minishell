#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#define HIDE 0
#define SHOW 1

typedef struct envp
{
    char        *key;
    char        *value;
    struct envp *next;
    int         display; //1 : show, 0 : hide
}   t_envp;

typedef struct node
{
    t_node  *left;
    t_node  *right;
    t_node  *papa;
    char    *str;
    char    *type;
}   t_node;


t_envp  *make_new_node(char *str);
char    *envp_split_val(char *str);
char    *envp_split_key(char *str);
void    free_envp(t_envp *head);

#endif