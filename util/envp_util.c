/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:50:28 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/30 18:25:43 by sojoo            ###   ########.fr       */
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

char	**dearrange_envp()
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
			if (envp[i] == NULL)
			{
				free_double_array(envp);
				return (NULL);
			}
			i += 1;
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
