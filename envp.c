/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:03:38 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/28 02:55:12 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
