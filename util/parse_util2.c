/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:52:18 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/31 17:05:14 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	check_valid(int i, int j, char *str)
{
	i += 1;
	if (str[i] == '\"' || str[i] == '\'')
		return (i);
	if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9'))
		return (i + 1);
	while (i <= j)
	{
		if ((str[i] < '0' || (str[i] > '9' && str[i] < 'A') || \
		(str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') && str[i] != '_')
			return (i);
		i += 1;
	}
	return (j);
}

int	check_valid_in_quotes(int i, int j, char *str)
{
	i += 1;
	if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9'))
		return (i + 1);
	while (i <= j)
	{
		if ((str[i] < '0' || (str[i] > '9' && str[i] < 'A') || \
		(str[i] > 'Z' && str[i] < 'a') || str[i] > 'z') && str[i] != '_')
			return (i);
		i += 1;
	}
	return (j);
}

void	free_tokenlist(t_token *tokenlist)
{
	t_token	*prev;

	while (tokenlist != NULL)
	{
		if (tokenlist->value)
			free(tokenlist->value);
		prev = tokenlist;
		tokenlist = tokenlist->next;
		free(prev);
	}
}

void	signal_exit_code(char *exitcode)
{
	t_envp	*env;
	char	*save;

	env = g_env;
	while (env)
	{
		if (ft_strequal(env->key, "?"))
		{
			save = env->value;
			env->value = exitcode;
			free(save);
			break ;
		}
		env = env->next;
	}
}
