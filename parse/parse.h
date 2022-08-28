/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:03:58 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/28 15:27:25 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../define.h"
# include "../util/util.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

//envp.c
t_envp	*arrange_envp(char **envp);

//token.c
void	execute_str(char *str, t_envp *env);
t_token	*tokenize(char *str);
t_token	*make_new_token(int type, char *value);
int		make_quotes_token(char *str, int i, int j, t_token **prev);

//token_after.c
int		after_tokenize(t_token *tokenlist, t_envp *env);
int		change_dollar(t_token *tokenlist, t_envp *env);
int		find_double_quotes(t_token *tokenlist, t_envp *env, int i);
int		change_dollar_single_quotes(t_token *tokenlist, int i);

//token_env.c
int		delete_quotes(t_token *token, int idx1, int idx2, char ch);
int		replace_value(t_token *tokenlist, t_envp *env, int i, int j);
int		no_env_key(t_token *tokenlist, int i, int j);

//token_find.c
int		envp_in_value(t_token *tokenlist, t_envp *env, int i, int j);
int		find_word(char *str, int i);
void	free_tokenlist(t_token *tokenlist);
void	preorder(t_node *root);

//token_what.c
int		tokenize_detail(char *str, int i, t_token **prev);
int		tokenize_quotes(char *str, int i, t_token **prev);
int		tokenize_pipe(char *str, int i, t_token **prev);
int		tokenize_redirect(char *str, int i, t_token **prev);
int		tokenize_word(char *str, int i, t_token **prev);

//into_ast.c
t_node	*into_ast(t_token *token);
int		while_ast(t_token *token, t_node *prev, t_node *n_head);
t_node	*root_node(t_token *token);
int		complete_line_node(t_node *prev, t_token *token, t_node *head);
int		redirect_or_command(t_node *prev, t_token **token);

//make_ast.c
int		make_line_node(t_node *prev, t_node *head, int direct);
int		make_pipe_node(t_node *prev, t_token *token);
int		make_new_command(t_node *prev, t_token *token);
int		make_new_redirect(t_node *prev, t_token *token, int direct);
t_node	*make_new_filename(t_node *prev, t_token *token);

#endif
