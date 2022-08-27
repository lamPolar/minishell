/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:03:58 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/27 23:31:14 by sojoo            ###   ########.fr       */
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

//token.c
int		find_word(char *str, int i);
char	*ft_strdup_idx(int i, int j, char *str);
t_token	*make_new_token(int type, char *value);
t_token	*tokenize(char *str);

void	execute_str(char *str, t_envp *env);

void	after_tokenize(t_token *tokenlist, t_envp *env);
int		delete_quotes(t_token *token, int idx1, int idx2, char ch);
int		change_dollar(t_token *tokenlist, t_envp *env);
int		find_double_quotes(t_token *tokenlist, t_envp *env, int i);
void	envp_in_value(t_token *tokenlist, t_envp *env, int i, int j);

//ast.c
t_node  *into_ast(t_token *token);
void    free_tree(t_node *head);
int make_line_node(t_node *prev, t_node *head);
int syntax_check_pipe(t_token *token, t_node *head);
int complete_line_node(t_node *prev, t_token *token);
int make_new_command(t_node *prev, t_token *token);
int right_in_redirect(t_node *prev, t_token *token);
t_node  *make_new_redirect(t_node *prev, t_token *token);
int syntax_check_redirect(t_token *token);
int make_pipe_node(t_node *prev, t_token *token);
t_node  *root_node(t_token *token);

#endif
