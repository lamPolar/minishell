/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 04:18:06 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/28 04:21:35 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	envp_in_value(t_token *tokenlist, t_envp *env, int i, int j)
{
	char	*envp;
	char	*new_value;

	envp = ft_strdup_idx(i + 1, j - 1, tokenlist->value);
	if (envp == NULL)
		return (0);
	while (env != NULL)
	{
		if (ft_strequal(envp, env->key))
		{
			if (replace_value(tokenlist, env, i, j) == 0)
				return (0);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
	{
		if (no_env_key(tokenlist, i, j) == 0)
			return (0);
	}
	free(envp);
	return (1);
}

int	find_word(char *str, int i)
{
	i++;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '|' && str[i] != '>' \
		&& str[i] != '<' && str[i] != '\'' && str[i] != '\"')
		i++;
	return (i);
}

void	free_tokenlist(t_token *tokenlist)
{
	t_token	*prev;

	while (tokenlist != NULL)
	{
		if (tokenlist->value)
			free(tokenlist->value);
		prev = tokenlist;
		tokenlist = tokenlist->next;
		free(prev);
	}
}

void	preorder(t_node *root)
{
	if (root->papa != NULL)
		printf("papa : %d / %s\n", root->papa->type, root->papa->str);
	printf("str : %s ", root->str);
	printf("type : %d \n", root->type);
	if (root->left)
	{
		printf("<");
		preorder(root->left);
	}
	if (root->right)
	{
		printf(">");
		preorder(root->right);
	}
}
