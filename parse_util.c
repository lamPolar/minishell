/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:40:26 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/27 20:27:56 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			index;
	unsigned char	*ptr;
	unsigned char	character;

	index = 0;
	ptr = (unsigned char *)b;
	character = (unsigned char)c;
	while (index < len)
	{
		ptr[index] = character;
		index++;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = (void *)malloc(count * size);
	if (new == NULL)
	{
		printf("kinder: %s\n", strerror(errno));
		return (NULL);
	}
	ft_memset(new, 0, count * size);
	return (new);
}

char    *ft_strdup_idx(int i, int j, char *str)
{
    char    *res;
    int     idx;

    res = (char *)malloc(sizeof(char) * (j - i + 2));
    if (!res)
        return (0);
    idx = 0;
    while (i <= j)
    {
        res[idx] = str[i];
        idx++;
        i++;
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
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (0);
	i = -1;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	len = 0;
	while (s2[len] != '\0')
		str[i++] = s2[len++];
	str[i] = '\0';
	if (flag)
	{
		free(s1);
		free(s2);
	}
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
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

int check_valid(int i, int j, char *str)
{
	i++;
	if (str[i] == '?')
		return (i + 1);
	while (i <= j)
    {
		if ((str[i] < 'A' || str[i] > 'z') && str[i] != '_' && \
			(str[i] < '0' || str[i] > '9'))
			return (i);
		i++;
	}
    return(j);
}

int ft_strequal(char *s1, char *s2)
{
    int i;
    int len1;
    int len2;
	
    i = 0;
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    if (len1 != len2)
        return (0);
    while (i < len1)
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}