/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:50:28 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/27 20:59:20 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

t_envp	*make_new_envp(char *str)
{
	t_envp	*new;

	new = (t_envp *)ft_calloc(sizeof(t_envp), 1);
	if (new == NULL)
		return (NULL);
	new->key = envp_split_key(str);
	new->value = envp_split_val(str);
	new->next = NULL;
	new->display = SHOW;
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
