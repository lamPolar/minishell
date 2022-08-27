/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:36:09 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 04:24:50 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// t_node.type
# define PIPE 1
# define LINE 2
# define REDIRECTION 3
# define COMMAND 4

// redirection mode : << < > >>
# define HEREDOC 10
# define INFILE 11
# define OUTFILE 12
# define APPEND_OUT 13

// envp.display
# define HIDE 20
# define SHOW 21

//token.type
# define PIPE_T 30
# define REDIRECT 31
# define WORD 32

typedef struct envp
{
	char		*key;
	char		*value;
	int			display;
	struct envp	*next;
}	t_envp;

typedef struct token
{
	int				type;
	char			*value;
	struct token	*next;
}	t_token;

typedef struct node
{
	struct node	*left;
	struct node	*right;
	struct node	*papa;
	char		*str;
	int			type;
}	t_node;

#endif