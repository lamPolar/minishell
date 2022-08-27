/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:28:47 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/27 20:49:22 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count += 1;
	return (count);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*new;
	size_t			index;
	unsigned char	*ptr;

	new = (void *)malloc(count * size);
	if (new == NULL)
	{
		printf("KINDER: %s\n", strerror(errno));
		return (NULL);
	}
	index = 0;
	ptr = (unsigned char *)new;
	while (index < count * size)
	{	
		ptr[index] = '\0';
		index += 1;
	}
	return (new);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	index = 0;
	if (dlen > dstsize)
		return (dstsize + slen);
	while (dlen + index + 1 < dstsize && src[index])
	{
		dst[dlen + index] = src[index];
		index += 1;
	}
	dst[dlen + index] = '\0';
	return (dlen + slen);
}

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	slen;

	slen = ft_strlen(s1);
	new = (char *)ft_calloc(sizeof(char), slen + 1);
	if (new == NULL)
		return (NULL);
	while (slen > 0)
	{	
		new[slen] = s1[slen];
		slen -= 1;
	}
	new[0] = s1[0];
	return (new);
}

static char	**ft_free_result(char **result, int total)
{
	int	index;
	int i;

	index = 0;
	while (index < total)
	{
		i = 0;
		while (i < ft_strlen(result[index]))
		{
			result[index][i] = '\0';
			i += 1;
		}
		free(result[index]);
		index++;
	}
	free(result);
	return (0);
}

static int	ft_check_words(const char *s, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (s[index])
	{
		if (s[index] != c)
		{
			count++;
			while (s[index] && s[index] != c)
				index++;
		}
		while (s[index] && s[index] == c)
			index++;
	}
	return (count);
}

static int	ft_count_word_len(const char *s, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (s[index] && s[index] == c)
		index++;
	while (s[index] && s[index] != c)
	{
		index++;
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*word;
	int		index;
	int		count_words;
	int		count_word_len;

	count_words = ft_check_words(s, c);
	result = (char **)ft_calloc(count_words + 1, sizeof(char *));
	if (!result)
		return (0);
	index = 0;
	result[count_words] = 0;
	while (index < count_words)
	{
		count_word_len = ft_count_word_len(s, c);
		word = (char *)ft_calloc(count_word_len + 1, sizeof(char));
		if (!word)
			return (ft_free_result(result, index));
		while (*s && *s == c)
			s++;
		ft_strlcat(word, s, count_word_len + 1);
		s += count_word_len;
		result[index++] = word;
	}
	return (result);
}