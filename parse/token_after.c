/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_after.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 04:15:30 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/31 14:28:57 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	after_tokenize(t_token *tokenlist)
{
	int		idx1;
	int		idx2;
	char	ch;

	while (tokenlist != NULL)
	{
		if (tokenlist->type == WORD)
		{
			if (change_dollar(tokenlist) == 0)
				return (0);
			idx1 = 0;
			idx2 = 0;
			ch = find_quotes(tokenlist->value, &idx1, &idx2);
			while (ch != 0)
			{
				if (delete_quotes(tokenlist, ch) == 0)
					return (0);
				idx1 = idx2 - 1;
				idx2 = 0;
				ch = find_quotes(tokenlist->value, &idx1, &idx2);
			}
		}
		tokenlist = tokenlist->next;
	}
	return (1);
}

int	change_dollar(t_token *tokenlist)
{
	int	i;
	int	j;

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
			j = check_valid(i, ft_strlen(tokenlist->value), tokenlist->value);
			if (envp_in_value(tokenlist, i, &j, 0) == 0)
				return (0);
			i = j - 1;
		}
	}
	return (1);
}

int	find_double_quotes(t_token *tokenlist, int i)
{
	int	j;

	j = i;
	while (tokenlist->value[++j] != '\0')
	{
		if (tokenlist->value[j] == '\"')
			break ;
	}
	if (tokenlist->value[j] != '\0')
	{
		while (i <= j)
		{
			if (tokenlist->value[i] == '$')
			{
				j = check_valid_in_quotes(i, j, tokenlist->value);
				if (envp_in_value(tokenlist, i, &j, 1) == 0)
					return (-1);
				i = j;
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
