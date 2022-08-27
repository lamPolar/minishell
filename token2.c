/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:35:24 by sojoo             #+#    #+#             */
/*   Updated: 2022/08/27 23:58:57 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//token.c 원본
//후처리 할 것 : $?

#include "parse.h"

int	find_word(char *str, int i)
{
	i++;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '|' && str[i] != '>' \
		&& str[i] != '<' && str[i] != '\'' && str[i] != '\"')
		i++;
	return (i);
}

t_token	*make_new_token(int type, char *value)
{
	t_token	*new;

	new = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*make_quotes_token(char *str, int i, int j, t_token *prev)
{
	t_token	*new;
	char	*word;

	if (str[j] == '\0')
		word = ft_strdup_idx(i, find_word(str, i) - 1, str);
	else
		word = ft_strdup_idx(i, find_word(str, j) - 1, str);
	new = NULL;
	if (str[i - 1] != ' ' && prev->type == WORD)
		prev->value = ft_strjoin(prev->value, word, 1); //flag1로 변경
	else
		new = make_new_token(WORD, word);
	return (new);
}

t_token	*tokenize(char *str)
{
	t_token	*res;
	t_token	*prev;
	t_token	*new;
	int		j;
	int		i;
	char	ch;

	res = make_new_token(-1, NULL);
	prev = res;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			continue ;
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			ch = str[i];
			j = i + 1;
			while (str[j] != '\0')
			{
				if (str[j] == ch)
					break ;
				j++;
			}
			new = make_quotes_token(str, i, j, prev);
			if (new)
			{
				prev->next = new;
				prev = prev->next;
			}
			if (str[j] == '\0')
				i = find_word(str, i);
			else
				i = find_word(str, j);
			continue ;
		}
		else if (str[i] == '|')
		{
			new = make_new_token(PIPE_T, ft_strdup_idx(i, i, str));
			prev->next = new;
			prev = prev->next;
			i++;
			continue ;
		}
		else if (str[i] == '>' || str[i] == '<')
		{
			ch = str[i];
			if (str[i + 1] == ch)
				j = i + 1;
			else
				j = i;
			new = make_new_token(REDIRECT, ft_strdup_idx(i, j, str));
			prev->next = new;
			prev = prev->next;
			i = j + 1;
			continue ;
		}
		else
		{
			j = find_word(str, i);
			new = make_new_token(WORD, ft_strdup_idx(i, j - 1, str));
			prev->next = new;
			prev = prev->next;
			i = j;
		}
	}
	return (res);
}

int	delete_quotes(t_token *token, int idx1, int idx2, char ch)
{
	char	*new;
	int		i;
	int		j;

	new = (char *)ft_calloc(ft_strlen(token->value) - 1, sizeof(char));
	if (new == NULL)
		return (0);
	i = 0;
	j = 0;
	while (token->value[i] != '\0')
	{
		if (token->value[i] != ch)
			new[j++] = token->value[i];
		i++;
	}
	free(token->value);
	token->value = new;
	return (1);
}

void	envp_in_value(t_token *tokenlist, t_envp *env, int i, int j)
{
	char	*envp;
	char	*new_value;
	int		size;
	int		idx;
	int		k;

	envp = ft_strdup_idx(i + 1, j - 1, tokenlist->value);
	while (env != NULL)
	{
		if (ft_strequal(envp, env->key))
		{
			size = ft_strlen(tokenlist->value) + ft_strlen(env->value) - j + i;
			new_value = (char *)ft_calloc(size, sizeof(char));
			idx = -1;
			while (++idx < i)
				new_value[idx] = tokenlist->value[idx];
			k = 0;
			while (idx < i + ft_strlen(env->value))
				new_value[idx++] = env->value[k++];
			while (j < ft_strlen(tokenlist->value))
				new_value[idx++] = tokenlist->value[j++];
			free(tokenlist->value);
			tokenlist->value = new_value;
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
	{
		size = ft_strlen(tokenlist->value) - j + i;
		new_value = (char *)ft_calloc(size, sizeof(char));
		idx = -1;
		while (++idx < i)
			new_value[idx] = tokenlist->value[idx];
		while (j < ft_strlen(tokenlist->value))
			new_value[idx++] = tokenlist->value[j++];
		free(tokenlist->value);
		tokenlist->value = new_value;
	}
	free(envp);
}

int	find_double_quotes(t_token *tokenlist, t_envp *env, int i)
{
	int	j;
	int	name_end;

	j = i + 1;
	while (tokenlist->value[j] != '\0')
	{
		if (tokenlist->value[j] == '\"')
			break ;
		j++;
	}
	if (tokenlist->value[j] != '\0')
	{
		while (i <= j)
		{
			if (tokenlist->value[i] == '$')
			{
				name_end = check_valid(i, j, tokenlist->value);
				envp_in_value(tokenlist, env, i, name_end);
				break ;
			}
			i++;
		}
		return (j);
	}
	return (i);
}

int	change_dollar(t_token *tokenlist, t_envp *env)
{
	int	i;
	int	j;

	i = 0;
	while(tokenlist->value[i] != '\0')
	{
		if (tokenlist->value[i] == '\"')
		{
			j = find_double_quotes(tokenlist, env, i);
			i = j + 1;
			continue ;
		}
		if (tokenlist->value[i] == '\'')
		{
			j = i + 1;
			while (tokenlist->value[j] && tokenlist->value[j] != '\'')
				j++;
			if (tokenlist->value[j] == '\0')
				i++;
			else
				i = j + 1;
			continue ;
		}
		if (tokenlist->value[i] == '$')
		{
			j = check_valid(i, ft_strlen(tokenlist->value), tokenlist->value);
			envp_in_value(tokenlist, env, i, j);
			i = j + 1;
			continue ;
		}
		i++;
	}
	return (1);
}

void	after_tokenize(t_token *tokenlist, t_envp *env)
{
	int		idx1;
	int		idx2;
	char	ch;

	while (tokenlist != NULL)
	{
		if (tokenlist->type == WORD)
		{
			if (change_dollar(tokenlist, env) == 0)
				return ;
			idx1 = 0;
			idx2 = 0;
			ch = find_quotes(tokenlist->value, &idx1, &idx2);
			while (ch != 0)
			{
				if (delete_quotes(tokenlist, idx1, idx2, ch) == 0)
					return ;
				idx1 = idx2 - 1;
				idx2 = 0;
				ch = find_quotes(tokenlist->value, &idx1, &idx2);
			}
		}
		tokenlist = tokenlist->next;
	}
}

void	preorder(t_node *root)
{
    if (root->papa != NULL)
        printf("papa : %d / %s\n", root->papa->type, root->papa->str);
	printf("str : %s ", root->str);
	printf("type : %d \n", root->type);
	if(root->left)
	{
        printf("<");
    	preorder(root->left);
    }
    if (root->right)
    {
        printf(">");
		preorder(root->right);
    }
}

void	execute_str(char *str, t_envp *env)
{
	t_token	*tokenlist;
	t_node	*ast;

	tokenlist = tokenize(str);
	if (tokenlist == NULL)
		return ;
	after_tokenize(tokenlist, env);
	ast = into_ast(tokenlist);
	if (ast == NULL)
    {
        // free_tokenlist(tokenlist); //만들기
		return ;
    }
    // preorder(ast);
    

	// int i = 0;
	// while (tokenlist != NULL)
	// {
	// 	printf("value:%s\ntype:%d\n\n", tokenlist->value, tokenlist->type);
	// 	tokenlist = tokenlist->next;
	// }
}

