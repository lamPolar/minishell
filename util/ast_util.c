#include "util.h"

t_node *make_new_node(char *str, int type, t_node *papa)
{
    t_node *new;

    new = (t_node *)ft_calloc(sizeof(t_node), 1);
    if (new == NULL)
        return (NULL);
    new->str = str;
    new->type = type;
    new->right = NULL;
    new->left = NULL;
    new->papa = papa;
    return (new);
}