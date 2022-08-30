/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:28:59 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/30 22:04:05 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

t_node	*make_new_node(char *str, int type, t_node *papa)
{
	t_node	*new;

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

t_node	*make_root_node(int i)
{
	t_node	*root;

	root = (t_node *)ft_calloc(1, sizeof(t_node));
	if (root == NULL)
		return (0);
	root->left = NULL;
	root->right = NULL;
	root->papa = NULL;
	root->str = NULL;
	if (i == PIPE)
		root->type = PIPE;
	else if (i == LINE)
		root->type = LINE;
	return (root);
}

int	syntax_check_pipe(t_token *token, t_node *head)
{
	if (token->next == NULL || token->next->type == PIPE_T)
	{
		print_error("KINDER: syntax error near unexpected token \'|\'", 0, 0, 0);
		free_tree(head);
		return (0);
	}
	return (1);
}

int	syntax_check_redirect(t_token *token)
{
	if (token->next == NULL)
		print_error("KINDER: syntax error near unexpected token 'newline'", 0, 0, 0);
	else if (token->next->type == REDIRECT)
		print_error("KINDER: syntax error near unexpected token \'", token->next->value, "\'", 0);		
	else if (token->next->type == PIPE_T)
		printf("KINDER: syntax error near unexpected token '|'\n");
	else
		return (1);
	return (0);
}

void	free_tree(t_node *head)
{
	if (head == NULL)
		return ;
	if (head->left)
		free_tree(head->left);
	if (head->right)
		free_tree(head->right);
	free(head);
}
