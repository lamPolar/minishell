/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_after.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 04:15:30 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/31 17:42:22 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	after_tokenize(t_token *tokenlist)
{
	t_token	*prev;

	prev = tokenlist;
	while (tokenlist != NULL)
	{
		if (tokenlist->type == WORD)
		{
			if (prev->type != REDIRECT || ft_strequal(prev->value, "<<") == 0)
			{
				if (change_dollar(tokenlist) == 0)
					return (0);
			}
			if (delete_quotes_loop(tokenlist) == 0)
				return (0);
		}
		prev = tokenlist;
		tokenlist = tokenlist->next;
	}
	return (1);
}

int	change_dollar(t_token *tokenlist)
{
	int	i;

	i = -1;
	while (tokenlist->value[++i] != '\0')
	{
		if (tokenlist->value[i] == '\"')
		{
			i = find_double_quotes(tokenlist, i);
			if (i == -1)
				return (0);
		}
		else if (tokenlist->value[i] == '\'')
			i = change_dollar_single_quotes(tokenlist, i);
		else if (tokenlist->value[i] == '$')
		{
			i = face_dollar_sign(i, ft_strlen(tokenlist->value), \
				0, tokenlist) - 1;
			if (i == -2)
				return (0);
		}
	}
	return (1);
}

int	delete_quotes_loop(t_token *tokenlist)
{
	int		idx1;
	int		idx2;
	char	ch;

	idx1 = 0;
	idx2 = 0;
	ch = find_quotes(tokenlist->value, &idx1, &idx2);
	while (ch != 0)
	{
		if (delete_quotes(tokenlist, ch, idx1, idx2) == 0)
			return (0);
		idx1 = idx2 - 1;
		idx2 = 0;
		ch = find_quotes(tokenlist->value, &idx1, &idx2);
	}
	return (1);
}

int	find_double_quotes(t_token *tokenlist, int i)
{
	int	j;

	j = find_quotes_index(i, tokenlist);
	if (tokenlist->value[j] != '\0')
	{
		while (i <= j)
		{
			if (tokenlist->value[i] == '$')
			{
				i = face_dollar_sign(i, j, 1, tokenlist) - 1;
				if (i == -2)
					return (-1);
				j = find_quotes_index(i, tokenlist);
			}
			i++;
		}
		return (j);
	}
	return (i);
}

int	change_dollar_single_quotes(t_token *tokenlist, int i)
{
	int	j;

	j = i + 1;
	while (tokenlist->value[j] && tokenlist->value[j] != '\'')
		j++;
	if (tokenlist->value[j] != '\0')
		i = j;
	return (i);
}
