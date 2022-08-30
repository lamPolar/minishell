/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:45:17 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/31 00:47:45 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

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

static char	**ft_free_result(char **result, int total)
{
	int	index;
	int	i;

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
