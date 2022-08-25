/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:40:26 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/24 15:29:07 by sojoo            ###   ########.fr       */
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
	if (!new)
	{
		printf("kinder: %s\n", strerror(errno));
		return (0);
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
