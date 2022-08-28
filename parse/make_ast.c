/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 03:59:19 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/28 12:36:15 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	make_line_node(t_node *prev, t_node *head, int direct)
{
	t_node	*new;

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
	if (direct == 1)
		prev->right = new;
	else if (direct == -1)
		prev->left = new;
	return (1);
}

int	make_pipe_node(t_node *prev, t_token *token)
{
	int		first_pipe;
	t_node	*new;

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

int	make_new_command(t_node *prev, t_token *token)
{
	t_node	*new;

	if (token->is_env == 1 && token->value[0] == '\0')
		return (1);
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

int	make_new_redirect(t_node *prev, t_token *token, int direct)
{
	t_node	*new;

	if (syntax_check_redirect(token) == 0)
		return (0);
	if (direct == 1)
	{
		prev = prev->left;
		while (prev->right != NULL)
			prev = prev->right;
	}
	new = (t_node *)ft_calloc(1, sizeof(t_node));
	if (new == NULL)
		return (0);
	new->right = NULL;
	new->left = make_new_filename(new, token);
	if (new->left == NULL)
		return (0);
	new->papa = prev;
	new->str = token->value;
	new->type = REDIRECTION;
	if (direct == 1)
		prev->right = new;
	else if (direct == -1)
		prev->left = new;
	return (1);
}

t_node	*make_new_filename(t_node *prev, t_token *token)
{
	t_node	*new;

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
