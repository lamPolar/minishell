/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:28:59 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/27 22:29:37 by heeskim          ###   ########.fr       */
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
