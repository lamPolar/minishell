/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 22:02:48 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/28 15:34:31 by heeskim          ###   ########.fr       */
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
int	builtin_cd(t_node *command, t_envp *env);
int	builtin_pwd(void);
int	builtin_exit(t_node *command, t_envp *env);

//builtin_export.c
int	export_with_argument(t_node *argument, t_envp *env);
int	builtin_export(t_node *command, t_envp *env);

//builtin_env.c
int	builtin_unset(t_node *command, t_envp *env);
int	builtin_env(t_envp *env);

//builtin_echo.c
int	check_n(char *str);
int	builtin_echo(t_node *command);

#endif