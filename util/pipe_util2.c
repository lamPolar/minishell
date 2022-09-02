/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 00:53:35 by sojoo             #+#    #+#             */
/*   Updated: 2022/09/02 13:37:57 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	ft_free(char *str)
{
	if (str)
		free(str);
	str = NULL;
	return (1);
}

void	free_double_array(char **string)
{
	int	i;

	i = 0;
	if (string == NULL)
		return ;
	while (string[i])
	{
		ft_free(string[i]);
		string[i] = NULL;
		i += 1;
	}
	free(string);
	string = NULL;
}

void	print_error(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
	if (str4)
		write(2, str4, ft_strlen(str4));
	write(2, "\n", 1);
}

int	check_heredoc(t_node *redirect)
{
	while (redirect != NULL && redirect->type == REDIRECTION)
	{
		if (ft_strequal(redirect->str, "<<") == 1)
			return (1);
		redirect = redirect->right;
	}
	return (0);
}
