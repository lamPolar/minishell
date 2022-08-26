/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:03:38 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/26 16:05:47 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_envp	*arrange_envp(char **envp)
{
	t_envp	*head;
	t_envp	*prev;
	t_envp	*new;
	int		cnt;

	head = make_new_envp(envp[0]);
	if (head == NULL)
		return (free_envp(head));
	prev = head;
	cnt = 0;
	while (envp[cnt] != NULL)
	{
		new = make_new_envp(envp[cnt]);
		if (new == NULL)
			return (free_envp(head));
		prev->next = new;
		prev = prev->next;
		cnt += 1;
	}
	return (head);
}

t_envp	*make_new_envp(char *str)
{
	t_envp	*new;

	new = (t_envp *)ft_calloc(sizeof(t_envp), 1);
	if (!new)
		return (NULL);
	new->key = envp_split_key(str); // key가 '\0'이면 저장가능?
	new->value = envp_split_val(str);
	new->next = NULL;
	new->display = 1;
	if (new->key == NULL || new->value == NULL) //둘중 하나가 말록 되었을 수도 있으므로 프리 필요
		return (NULL);
	return (new);
}

char	*envp_split_key(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i] != '=')
		i += 1;
	res = (char *)ft_calloc(sizeof(char), i + 1);
	if (res == NULL)
		return (0);
	i = 0;
	while (str[i] != '=')
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
	while (str[i] != '=')
		i += 1;
	i += 1;
	j = 0;
	while (str[i + j] != '\0')
		j += 1;
	res = (char *)ft_calloc(sizeof(char), j + 1);
	if (res == NULL)
		return (NULL);
	j = 0;
	while (str[i] != '\0')
	{
		res[j] = str[i];
		i += 1;
		j += 1;
	}
	res[j] = '\0';
	return (res);
}

t_envp	*free_envp(t_envp *head)
{
	t_envp	*prev;

	while (head != NULL)
	{
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		prev = head;
		head = head->next;
		free(prev);
	}
	return (NULL);
}
