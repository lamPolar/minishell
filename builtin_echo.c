/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:45:54 by heeskim           #+#    #+#             */
/*   Updated: 2022/08/24 17:45:56 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int builtin_echo(int argc, char *argv[], t_envp *env)
{
	//-n 옵션 : newline character을 제외하고 출력 : 마지막 개행만 존재?
	//환경변수 치환하기 : ""일때
	//''일때: 환경변수 그대로 출력
	//$? : exit_status출력 : global 로 사용해야할까?
	//echo -nnnnnnnnnnnn fdjksl: echo -n fdjksl과 동일하게 취급
	//echo hello ;;
	//echo hello | |
	//echo hello ; ; 등등 -> bash: syntax error near unexpected token `|' 에러 출력
	
}
