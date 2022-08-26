/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:48 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/26 15:59:39 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "parse.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

typedef struct node
{
	t_node	*left;
	t_node	*right;
	t_node	*papa;
	char	*str;
	char	*type;
}	t_node;

# define PIPE 1
# define LINE 2
# define REDIRECTION 3
# define COMMAND 4
#endif