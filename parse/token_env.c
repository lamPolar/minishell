/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 04:16:58 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/31 17:42:39 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	delete_quotes(t_token *token, char ch, int idx1, int idx2)
{
	char	*new;
	int		i;
	int		j;

	new = (char *)ft_calloc(ft_strlen(token->value) - 1, sizeof(char));
	if (new == NULL)
		return (0);
	i = 0;
	j = 0;
	while (token->value[i] != '\0')
	{
		if (token->value[i] != ch || (i > idx2 || idx1 > i))
			new[j++] = token->value[i];
		i++;
	}
	free(token->value);
	token->value = new;
	return (1);
}

int	replace_value(t_token *tokenlist, t_envp *env, int i, int *j)
{
	int		size;
	int		idx;
	int		k;
	char	*new_value;

	size = ft_strlen(tokenlist->value) + ft_strlen(env->value) - *j + i;
	new_value = (char *)ft_calloc(size, sizeof(char));
	if (new_value == NULL)
		return (0);
	idx = -1;
	while (++idx < i)
		new_value[idx] = tokenlist->value[idx];
	k = 0;
	while (idx < i + ft_strlen(env->value))
		new_value[idx++] = env->value[k++];
	while (*j < ft_strlen(tokenlist->value))
		new_value[idx++] = tokenlist->value[(*j)++];
	new_value[idx] = '\0';
	*j = i + ft_strlen(env->value);
	free(tokenlist->value);
	tokenlist->value = new_value;
	tokenlist->is_env = 1;
	return (1);
}

int	no_env_key(t_token *tokenlist, int i, int *j)
{
	int		size;
	int		idx;
	char	*new_value;

	size = ft_strlen(tokenlist->value) - *j + i + 1;
	new_value = (char *)ft_calloc(size, sizeof(char));
	if (new_value == NULL)
		return (0);
	idx = -1;
	while (++idx < i)
		new_value[idx] = tokenlist->value[idx];
	while (*j < ft_strlen(tokenlist->value))
		new_value[idx++] = tokenlist->value[(*j)++];
	*j = i;
	free(tokenlist->value);
	tokenlist->value = new_value;
	tokenlist->is_env = 1;
	return (1);
}
