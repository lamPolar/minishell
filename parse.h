/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:03:58 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/27 20:59:46 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "define.h"
# include "util/util.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

//envp.c
t_envp	*arrange_envp(char **envp);

int		find_word(char *str, int i);
char	*ft_strdup_idx(int i, int j, char *str);
t_token	*make_new_token(int type, char *value);
t_token	*tokenize(char *str);

void	execute_str(char *str, t_envp *env);

void    after_tokenize(t_token *tokenlist, t_envp *env);
int 	delete_quotes(t_token *token, int idx1, int idx2, char ch);
int 	change_dollar(t_token *tokenlist, t_envp *env);
int 	find_double_quotes(t_token *tokenlist, t_envp *env, int i);
void    envp_in_value(t_token *tokenlist, t_envp *env, int i, int j);

#endif
