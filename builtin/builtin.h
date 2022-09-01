/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:48 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/01 17:30:33 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../define.h"
# include "../util/util.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# define PWD 0
# define OLDPWD 1

//builtin.c
int		builtin_pwd(void);
int		builtin_exit(t_node *command, t_node *ast, t_token *token);
void	numeric_exit(char *str, t_node *ast, t_token *token);

//builtin_cd.c
int		check_home(char **str, char *home);
int		check_oldpwd(char **str);
int		update_pwd(int flag);
int		builtin_cd(t_node *command);

//builtin_export.c
int		export_with_argument(t_node *argument);
int		builtin_export(t_node *command);
int		change_env_show(char *str);
t_envp	*sort_envp(int size, int i);

//builtin_env.c
char	*get_env_value(char *key);
int		builtin_unset(t_node *command);
int		builtin_env(void);

//builtin_echo.c
int		check_n(char *str);
int		builtin_echo(t_node *command);

#endif
