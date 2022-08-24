/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:17:29 by heeskim           #+#    #+#             */
/*   Updated: 2021/12/06 16:47:33 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_result(char **result, int total)
{
	int	index;

	index = 0;
	while (index < total)
	{
		ft_bzero(result[index], ft_strlen(result[index]));
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
		ft_strlcpy(word, s, count_word_len + 1);
		s += count_word_len;
		result[index++] = word;
	}
	return (result);
}
