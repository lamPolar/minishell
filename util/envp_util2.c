/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:55:51 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/31 03:28:03 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

char	**dearrange_envp(void)
{
	char	**envp;
	int		size;
	int		i;
	t_envp	*env;

	env = g_env;
	size = get_env_size(env);
	envp = (char **)ft_calloc(sizeof(char *), size + 1);
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (env->display == SHOW)
		{	
			envp[i] = ft_strjoin_three(env->key, "=", env->value);
			if (envp[i++] == NULL)
			{
				free_double_array(envp);
				return (NULL);
			}
		}
		env = env->next;
	}
	return (envp);
}

int	get_env_size(t_envp *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head->display == SHOW)
			i += 1;
		head = head->next;
	}
	return (i);
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
