/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:50:28 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 02:44:39 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

t_envp	*make_new_envp(char *str, int display)
{
	t_envp	*new;

	new = (t_envp *)ft_calloc(sizeof(t_envp), 1);
	if (new == NULL)
		return (NULL);
	new->key = envp_split_key(str);
	new->value = envp_split_val(str);
	new->next = NULL;
	new->display = display;
	if (new->key == NULL || new->value == NULL)
	{
		free_both(new->key, new->value);
		return (NULL);
	}
	return (new);
}

char	*envp_split_key(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i += 1;
	res = (char *)ft_calloc(sizeof(char), i + 1);
	if (res == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		res[i] = str[i];
		i += 1;
	}
	res[i] = '\0';
	return (res);
}

char	*envp_split_val(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i += 1;
	i += 1;
	j = 0;
	while (str[i + j])
		j += 1;
	res = (char *)ft_calloc(sizeof(char), j + 1);
	if (res == NULL)
		return (NULL);
	j = 0;
	while (str[i])
	{
		res[j] = str[i];
		i += 1;
		j += 1;
	}
	res[j] = '\0';
	return (res);
}

t_envp	*arrange_envp(char **envp)
{
	t_envp	*head;
	t_envp	*prev;
	t_envp	*new;
	int		cnt;

	head = make_new_envp(envp[0], SHOW);
	if (head == NULL)
		return (free_envp(head));
	prev = head;
	cnt = 1;
	while (envp[cnt])
	{
		new = make_new_envp(envp[cnt], SHOW);
		if (new == NULL)
			return (free_envp(head));
		prev->next = new;
		prev = prev->next;
		cnt += 1;
	}
	new = make_new_envp("?=0", HIDE);
	if (new == NULL)
		return (free_envp(head));
	prev->next = new;
	return (head);
}
