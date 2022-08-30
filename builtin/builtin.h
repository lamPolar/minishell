/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:48 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/31 00:28:38 by sojoo            ###   ########.fr       */
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

//builtin.c
int		builtin_pwd(void);
int		builtin_exit(t_node *command, t_node *ast, t_token *token);
void	numeric_exit(char *str, t_node *ast, t_token *token);

//builtin_cd.c
int		check_home(t_node *command);
int		check_oldpwd(t_node *command);
char	*make_pwd(char *str, char **pwd);
int		change_pwd(char *oldpwd, char *pwd);
int		builtin_cd(t_node *command);

//builtin_export.c
int		export_with_argument(t_node *argument);
int		builtin_export(t_node *command);
int		change_env_show(char *str);

//builtin_env.c
int		builtin_unset(t_node *command);
int		builtin_env(void);

//builtin_echo.c
int		check_n(char *str);
int		builtin_echo(t_node *command);

#endif
