/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_what.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 04:19:20 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/28 12:51:17 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	tokenize_detail(char *str, int i, t_token **prev)
{
	if (str[i] == '\'' || str[i] == '\"')
	{
		i = tokenize_quotes(str, i, prev);
		if (i == -1)
			return (-1);
	}
	else if (str[i] == '|')
	{
		i = tokenize_pipe(str, i, prev);
		if (i == -1)
			return (-1);
	}
	else if (str[i] == '>' || str[i] == '<')
	{
		i = tokenize_redirect(str, i, prev);
		if (i == -1)
			return (-1);
	}
	else
	{
		i = tokenize_word(str, i, prev);
		if (i == -1)
			return (-1);
	}
	return (i);
}

int	tokenize_quotes(char *str, int i, t_token **prev)
{
	int		j;
	char	ch;

	ch = str[i];
	j = i + 1;
	while (str[j] != '\0')
	{
		if (str[j] == ch)
			break ;
		j++;
	}
	if (make_quotes_token(str, i, j, prev) == 0)
		return (-1);
	if (str[j] == '\0')
		i = find_word(str, i);
	else
		i = find_word(str, j);
	return (i);
}

int	tokenize_pipe(char *str, int i, t_token **prev)
{
	t_token	*new;

	new = make_new_token(PIPE_T, ft_strdup_idx(i, i, str));
	if (new == NULL)
		return (-1);
	(*prev)->next = new;
	*prev = (*prev)->next;
	i++;
	return (i);
}

int	tokenize_redirect(char *str, int i, t_token **prev)
{
	int		j;
	char	ch;
	t_token	*new;

	ch = str[i];
	if (str[i + 1] == ch)
		j = i + 1;
	else
		j = i;
	new = make_new_token(REDIRECT, ft_strdup_idx(i, j, str));
	if (new == NULL)
		return (-1);
	(*prev)->next = new;
	*prev = (*prev)->next;
	i = j + 1;
	return (i);
}

int	tokenize_word(char *str, int i, t_token **prev)
{
	int		j;
	t_token	*new;

	j = find_word(str, i);
	new = make_new_token(WORD, ft_strdup_idx(i, j - 1, str));
	if (new == NULL)
		return (-1);
	(*prev)->next = new;
	*prev = (*prev)->next;
	i = j;
	return (i);
}
