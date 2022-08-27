/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:49:48 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/27 20:25:20 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_node  *into_ast(t_token *token)
{
    t_token *t_head;
    t_node  *n_head;
    t_node  *prev;
    t_node  *new;

    t_head = token;
    n_head = root_node(token);
    if (n_head == NULL)
        return (0);
    prev = n_head;
    if (make_pipe_node(prev, token) == 0)
    {
        free_node(n_head);
        return (0);
    }
    
}

int make_pipe_node(t_node *prev, t_token *token)
{
    int     first_pipe;
    t_node  *new;

    first_pipe = 0;
    while (token != NULL)
    {
        if (token->type == PIPE && first_pipe == 0)
            first_pipe = 1;
        else if (token->type == PIPE && first_pipe == 1)
        {
            new = (t_node *)ft_calloc(1, sizeof(t_node));
            if (new == NULL)
                return (0);
            new->left = NULL;
            new->right = NULL;
            new->papa = prev;
            new->str = NULL;
            new->type = PIPE;
            prev->right = new;
            prev = prev->right;
        }
        token = token->next;
    }
    return (1);
}

t_node  *root_node(t_token *token)
{
    t_node  *root;

    while (token != NULL)
    {
        if (token->type == PIPE)
        {
            root = (t_node *)ft_calloc(1, sizeof(t_node));
            if (root == NULL)
                return (0);
            root->left = NULL;
            root->right = NULL;
            root->papa = NULL;
            root->str = NULL;
            root->type = PIPE;
            return (root);
        }
        token = token->next;
    }
    //다 돌았는데도 파이프가 없다면 LINE이 루트
    root = (t_node *)ft_calloc(1, sizeof(t_node));
    if (root = NULL)
        return (0);
    root->left = NULL;
    root->right = NULL;
    root->papa = NULL;
    root->str = NULL;
    root->type = LINE;
    return (root);
}