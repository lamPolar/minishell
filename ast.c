/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:49:48 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/27 23:59:20 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_node  *into_ast(t_token *token)
{
    t_node  *n_head;
    t_node  *prev;

    n_head = root_node(token); //root 노드 만들기 (PIPE or LINE)
    if (n_head == NULL)
        return (0);
    if (syntax_check_pipe(token, n_head) == 0)
        return (0);
    prev = n_head;
    if (make_pipe_node(prev, token) == 0) //PIPE 노드들 미리 만들어서 오른쪽으로 연결해주기
    {
        free_tree(n_head); //free_tree 함수 만들기
        return (0);
    }
    token = token->next;
    while (token != NULL)
    {
        if (complete_line_node(prev, token) == 0) //line 노드밑으로 하나의 line 완성하기
        {
            free_tree(n_head);
            return (0);
        }
        while (token != NULL && token->type != PIPE_T) //파이프 전까지 토큰 이동
            token = token->next;
        if (token == NULL)
            break ;
        if (token->type == PIPE_T) //파이프 토큰 발견시 다음도 파이프인지 문법 검사
        {
            if (syntax_check_pipe(token, n_head) == 0)
                return (0);
        }
        token = token->next;
        if (prev->right == NULL) //오른쪽 노드가 파이프가 아니라면 라인노드 생성
        {
            if (make_line_node(prev, n_head) == 0)
                return (0);
        }
        prev = prev->right; //파이프 혹은 라인 노드로 이동 (오른쪽)
    }
    return (n_head);
}

void    free_tree(t_node *head)
{
    if (head == NULL)
        return ;
    if (head->left)
        free_tree(head->left);
    if (head->right)
        free_tree(head->right);
    free(head);
}

int make_line_node(t_node *prev, t_node *head)
{
    t_node  *new;

    new = (t_node *)ft_calloc(1, sizeof(t_node));
    if (new == NULL)
    {
        free_tree(head);
        return (0);
    }
    new->left = NULL;
    new->right = NULL;
    new->papa = prev;
    new->str = NULL;
    new->type = LINE;
    prev->right = new;
    return (1);
}

int syntax_check_pipe(t_token *token, t_node *head)
{
    if (token->next->type == PIPE_T)
    {
        printf("KINDER: syntax error near unexpected token '|'\n");
        free_tree(head);
        return (0);
    }
    return (1);
}

int complete_line_node(t_node *prev, t_token *token)
{
    t_node  *new;

    if (prev->type == PIPE)
    {
        new = (t_node *)ft_calloc(1, sizeof(t_node));
        if (new == NULL)
            return (0);
        new->left = NULL;
        new->right = NULL;
        new->papa = prev;
        new->str = NULL;
        new->type = LINE;
        prev->left = new;
        prev = prev->left;
    }
    while (token != NULL && token->type != PIPE_T)
    {
        if (token->type == REDIRECT && prev->left == NULL)
        {
            if (syntax_check_redirect(token) == 0)
                return (0);
            new = (t_node *)ft_calloc(1, sizeof(t_node));
            if (new == NULL)
                return (0);
            new->right = NULL;
            new->left = make_new_redirect(new, token);
            if (new->left == NULL)
                return (0);
            new->papa = prev;
            new->str = token->value;
            new->type = REDIRECTION;
            prev->left = new;
            token = token->next;
        }
        else if (token->type == REDIRECT)
        {
            if (right_in_redirect(prev, token) == 0)
                return (0);
            token = token->next;
        }
        else
        {
            if (make_new_command(prev, token) == 0)
                return (0);
        }
        token = token->next;
    }
    return (1);
}

int make_new_command(t_node *prev, t_token *token)
{
    t_node  *new;

    while (prev->right != NULL)
        prev = prev->right;
    new = (t_node *)ft_calloc(1, sizeof(t_node));
    if (new == NULL)
        return (0);
    new->right = NULL;
    new->left = NULL;
    new->papa = prev;
    new->str = token->value;
    new->type = COMMAND;
    prev->right = new;
    return (1);
}

int right_in_redirect(t_node *prev, t_token *token)
{
    t_node  *new;

    if (syntax_check_redirect(token) == 0)
        return (0);
    prev = prev->left;
    while (prev->right != NULL)
        prev = prev->right;
    new = (t_node *)ft_calloc(1, sizeof(t_node));
    if (new == NULL)
        return (0);
    new->right = NULL;
    new->left = make_new_redirect(new, token);
    if (new->left == NULL)
        return (0);
    new->papa = prev;
    new->str = token->value;
    new->type = REDIRECTION;
    prev->right = new;
    return (1);
}

t_node  *make_new_redirect(t_node *prev, t_token *token)
{
    t_node  *new;

    new = (t_node *)ft_calloc(1, sizeof(t_node));
    if (new == NULL)
        return (0);
    new->right = NULL;
    new->left = NULL;
    new->papa = prev;
    new->str = token->next->value;
    new->type = REDIRECTION;
    return (new);
}

int syntax_check_redirect(t_token *token)
{
    if (token->next == NULL)
        printf("KINDER: syntax error near unexpected token 'newline'\n");
    else if (token->next->type == REDIRECT)
        printf("KINDER: syntax error near unexpected token '%s'\n", token->next->value);
    else if (token->next->type == PIPE_T)
        printf("KINDER: syntax error near unexpected token '|'\n");
    else
        return (1);
    return (0);
}

int make_pipe_node(t_node *prev, t_token *token)
{
    int     first_pipe;
    t_node  *new;

    first_pipe = 0;
    while (token != NULL)
    {
        if (token->type == PIPE_T && first_pipe == 0)
            first_pipe = 1;
        else if (token->type == PIPE_T && first_pipe == 1)
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
        if (token->type == PIPE_T)
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
    if (root == NULL)
        return (0);
    root->left = NULL;
    root->right = NULL;
    root->papa = NULL;
    root->str = NULL;
    root->type = LINE;
    return (root);
}