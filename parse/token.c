/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:35:24 by sojoo             #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2022/08/28 04:49:48 by sojoo            ###   ########.fr       */
=======
/*   Updated: 2022/08/28 04:32:29 by heeskim          ###   ########.fr       */
>>>>>>> df05211eb4f147ab5b7fc6d01f98abeac76b3d14
=======
/*   Updated: 2022/08/28 13:37:21 by heeskim          ###   ########.fr       */
>>>>>>> d72f3592e6b9d51185d5a56245380c3833ecdb2c
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../pipe.h"

void	execute_str(char *str, t_envp *env)
{
	t_token	*tokenlist;
	t_node	*ast;

	tokenlist = tokenize(str);
	if (tokenlist == NULL)
		return ;
	if (after_tokenize(tokenlist, env) == 0 || tokenlist->next == NULL)
	{
		free_tokenlist(tokenlist);
		return ;
	}
	ast = into_ast(tokenlist);
	if (ast == NULL)
	{
		free_tokenlist(tokenlist);
		return ;
	}
	// preorder(ast);
	execute_tree(ast, env);

	// int i = 0;
	// while (tokenlist != NULL)
	// {
	// 	printf("value:%s\ntype:%d\n\n", tokenlist->value, tokenlist->type);
	// 	tokenlist = tokenlist->next;
	// }
	free_tree(ast);
	free_tokenlist(tokenlist);
}

t_token	*tokenize(char *str)
{
	t_token	*res;
	t_token	*prev;
	int		i;

	res = make_new_token(-1, NULL);
	if (res == NULL)
		return (0);
	prev = res;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
		}
		else
		{
			i = tokenize_detail(str, i, &prev);
			if (i == -1)
				return (0);
		}
	}
	return (res);
}

t_token	*make_new_token(int type, char *value)
{
	t_token	*new;

	new = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

int	make_quotes_token(char *str, int i, int j, t_token **prev)
{
	t_token	*new;
	char	*word;

	if (str[j] == '\0')
		word = ft_strdup_idx(i, find_word(str, i) - 1, str);
	else
		word = ft_strdup_idx(i, find_word(str, j) - 1, str);
	if (word == NULL)
		return (0);
	if (str[i - 1] != ' ' && (*prev)->type == WORD)
	{
		(*prev)->value = ft_strjoin((*prev)->value, word, 1);
		if ((*prev)->value == NULL)
			return (0);
	}
	else
	{
		new = make_new_token(WORD, word);
		if (new == NULL)
			return (0);
		(*prev)->next = new;
		*prev = (*prev)->next;
	}
	return (1);
}