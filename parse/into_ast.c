/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   into_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:49:48 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/28 15:40:10 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_node	*into_ast(t_token *token)
{
	t_node	*n_head;
	t_node	*prev;

	n_head = root_node(token);
	if (n_head == NULL)
		return (0);
	if (syntax_check_pipe(token, n_head) == 0)
		return (0);
	prev = n_head;
	if (make_pipe_node(prev, token) == 0)
	{
		free_tree(n_head);
		return (0);
	}
	token = token->next;
	if (while_ast(token, prev, n_head) == 0)
		return (0);
	return (n_head);
}

int	while_ast(t_token *token, t_node *prev, t_node *n_head)
{
	while (token != NULL)
	{
		if (complete_line_node(prev, token, n_head) == 0)
			return (0);
		while (token != NULL && token->type != PIPE_T)
			token = token->next;
		if (token == NULL)
			break ;
		if (token->type == PIPE_T)
		{
			if (syntax_check_pipe(token, n_head) == 0)
				return (0);
		}
		token = token->next;
		if (prev->right == NULL)
		{
			if (make_line_node(prev, n_head, 1) == 0)
				return (0);
		}
		prev = prev->right;
	}
	return (1);
}

t_node	*root_node(t_token *token)
{
	t_node	*root;

	while (token != NULL)
	{
		if (token->type == PIPE_T)
		{
			root = make_root_node(PIPE);
			if (root == NULL)
				return (0);
			return (root);
		}
		token = token->next;
	}
	root = make_root_node(LINE);
	if (root == NULL)
		return (0);
	return (root);
}

int	complete_line_node(t_node *prev, t_token *token, t_node *head)
{
	//t_node	*new;

	if (prev->type == PIPE)
	{
		if (make_line_node(prev, head, -1) == 0)
			return (0);
		prev = prev->left;
	}
	while (token != NULL && token->type != PIPE_T)
	{
		if (redirect_or_command(prev, &token) == 0)
		{
			free_tree(head);
			return (0);
		}
	}
	return (1);
}

int	redirect_or_command(t_node *prev, t_token **token)
{
	if ((*token)->type == REDIRECT && prev->left == NULL)
	{
		if (make_new_redirect(prev, *token, -1) == 0)
			return (0);
		*token = (*token)->next;
	}
	else if ((*token)->type == REDIRECT)
	{
		if (make_new_redirect(prev, *token, 1) == 0)
			return (0);
		*token = (*token)->next;
	}
	else
	{
		if (make_new_command(prev, *token) == 0)
			return (0);
	}
	*token = (*token)->next;
	return (1);
}
