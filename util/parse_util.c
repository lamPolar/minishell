/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:40:26 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/30 21:58:44 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

char	*ft_strdup_idx(int i, int j, char *str)
{
	char	*res;
	int		idx;

	res = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!res)
		return (0);
	idx = 0;
	while (i <= j)
	{
		res[idx] = str[i];
		idx += 1;
		i += 1;
	}
	res[idx] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2, int flag)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	if (*s1 == '\0' && *s2 == '\0')
		len = 1;
	else
		len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)ft_calloc(sizeof(char), len);
	if (!str)
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	len = 0;
	while (s2[len] != '\0')
		str[i++] = s2[len++];
	if (flag)
	{
		free(s1);
		free(s2);
	}
	return (str);
}

char	find_quotes(char *str, int *first, int *second)
{
	char	ch;

	while (str[*first] != '\0')
	{
		if (str[*first] == '\'' || str[*first] == '\"')
		{
			ch = str[*first];
			*second = *first + 1;
			while (str[*second] != '\0' && str[*second] != ch)
				*second += 1;
			if (str[*second] == '\0')
				return (0);
			else
				return (ch);
		}
		*first += 1;
	}
	return (0);
}

int	check_valid(int i, int j, char *str)
{
	i += 1;
	if (str[i] == '?' || str[i] == '$' || (str[i] >= '0' && str[i] <= '9'))
		return (i + 1);
	while (i <= j)
	{
		if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z') \
			&& str[i] != '_' && (str[i] <= '0' || str[i] >= '9') || str[i] == '=')
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

void    signal_exit_code(char *exitcode)
{
    t_envp  *env;
    char    *save;

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
