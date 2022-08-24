#include "builtin.h"
#include <errno.h>

int ft_strequal(char *s1, char *s2)
{
	int i;
	int len1;
	int len2;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (0);
	while (i < len1)
	{
		if (s1[i] != s2[i])
			return(0);
		i++;
	}
	return (1);
}

int	builtin_cd(t_node *command, t_envp *env)
{
	int		result;
	char	*home;
	
	if (command->right == NULL || ft_strequal(command->right->str, "~")) //매개변수가 없으면
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			printf("kinder: cd: HOME not set\n");
			return (1);
		}
		if (chdir(home) == -1)
		{
			printf("cd: HOME: %s\n", strerror(errno));
			return (1);
		}
	}
	else
	{
		if (chdir(command->right->str) == -1)
		{
			printf("cd: %s: %s\n", command->right, strerror(errno));
			return (1);
		}
	}
	return (0);
}

int check_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return(1);
		i++;
	}
	return(0);
}

int check_invalid(char *str)
{
	if ((str[0] < '0' || str[0] > '9') && str[0] != '_')
		return(1);
	return(0);
}

int	change_env_value(char *str, t_envp *env)
{
	char *value;

	value = envp_split_val(str);
	if (value == NULL)
		return (1);
	free(env->value);
	env->value = value;
	env->display = SHOW;
	return (0);
}

int add_to_env(char *str, t_envp *env)
{
	t_envp	*new;
	char	*key;
	char	*value;

	key = envp_split_key(str);
	if (key == NULL)
		return (1);
	while (env->next)
	{
		if (ft_strequal(env->key, new->key))
			return (change_env_value(str, env));
		env = env->next;
	}
	if (ft_strequl(env->key, new->key))
		return (change_env_value(str, env));
	else if (env->next == NULL)
	{
		new = make_new_node(str);
		if (new == NULL)
			return (1);
		env->next = new;
	}
}

int builtin_export(t_node *command, t_envp *env)
{
	t_envp *new;
	t_node *argument;
	

	if (command->right == NULL)
	{
		//env 오름차순 sorting??
		while (env)
		{
			if (env->display == SHOW)
			printf("declare -x %s = \"%s\"\n", env->key, env->value);
			env = env->next;
		}
		return (1);
	}
	else
	{
		argument = command->right;
		if (check_equal(argument->str)) // = 있으면 1리턴
		{
			if (check_invalid(argument->str))
				printf("KINDER: export: \'%s\': not a valid identifier\n", argument->str);
			add_to_env(argument->str, env);
		}
		else // =이 없다면
		{
			while (env)
			{
				if (ft_strequal(env->key, argument->str)) //맞는 env가 있다면 
				{
					env->display = SHOW;
					return (0);
				}
				env = env->next;
			}
		}
	}
	//만약 파이프 뒤에 export를 호출하면, 자식프로세스에 대한 export이므로 환경변수에 대해서 변경하지 않음
}

int builtin_pwd(t_node *command)
{
	char *buf;
	size_t size;

	buf = NULL;
	buf = getcwd(buf, size);
	if (buf == NULL)
	{
		printf("KINDER: pwd: %s", strerror(errno));
		return (1);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

int max(int len1, int len2)
{
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

int builtin_unset(t_node *command, t_envp **head)
{
	int len;
	int len2;
	t_envp *prev;
	t_envp *env;

	//환경변수가 유효한지 확인 -> 문자/숫자/_로 시작해야한다.
	//이미 존재하는 환경변수인지 확인 -> 있으면 삭제 
	//만약 파이프 뒤에서 unset을 실행하면 자식프로세스에 대한 unset이므로, 환경변수 삭제 x
	if (argc == 0)
	{
		printf("USAGE: unset [KEY]\n");
		return(1);
	}
	else
	{
		len = ft_strlen(argv[1]);
		env = *head;
		while (env)
		{
			len2 = ft_strlen(env->key);
			if (ft_strncmp(argv[1], env->key, max(len, len2)) == 0)
			{
				if (prev == env)
					*head = env->next;
				else
					prev->next = env->next;
				free(env->key);
				free(env->value);
				free(env);
				return (0);
			}
			prev = env;
			env = env->next;
		}
	}
}
 //어떤 argument가 함께 들어오든지, env만 출력?
int builtin_env(t_envp *env)
{
	while (env)
	{
		if (env->display == SHOW)
			printf("%s = %s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int ft_isnum(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || str[i] != '+' || str[i] != '-' \
			|| str[i] < 9 || str[i] > 13 || str[i] != 32)
			return (0);
		i += 1;
	}
	return (1);
}

int builtin_exit(t_node *command)
{
	t_node *argument;

	if (command->right == NULL)
		exit(EXIT_SUCCESS);
	else
	{
		argument = command->right;
		if (argument->right == NULL)
		{
			if (ft_isnum(argument->str))
				exit(ft_atoi(argument->str));
			else
				printf("exit\nkinder: exit: %s: numberic argument required",\
						argument->str);
				exit(255);
		}   
		else
			printf("exit\nkinder: exit: too many arguments\n");
		
	}
	/*
	exit만 입력시 -> exit출력 후 exit_success를 넘기면서 종료
	exit뒤에 인자가 있으면, 부모에게 상태값으로 전달 -> exit출력하고 종료
	만약 exit뒤에 인자가 두개 이상 있으면,
	exit\n
	bash: exit: too many arguments 
	출력후 종료 x
	만약 exit뒤에 숫자가 아니면,
	exit\n
	bash: exit: a: numeric argument required
	출력후 종료
	파이프 뒤에 있으면, 자식프로세스의 exit이기 때문에 쉘 종료 x
	그러나 $?에는 해당 exit의 값이 있음*/
}

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

int main(int argc, char **argv)
{

	while (1) {}
	return (0);
}
