#include "builtin.h"

int builtin_cd(int argc, char *argv)
{
    //cd ~일때 home으로 변경
    //cd $변수 -> 변수 찾아서 이동 (만약에 없는 환경변수이면 home으로 이동) 
    //cd $HOME -> home변수가 없으면 (unset : bash: cd: HOME not set 메세지 출력)
    //cd ~ 234 : home으로 이동 : path가 2개 들어오면 -> 앞에거 기준으로 이동
    // 올바르지 않은 폴더 경로일 때 : no such file or directory
    // .과  ..에 대해서 ?
    int result;

    if (argc == 0)
    {
        result = chdir(getenv("HOME"));
        if (result == -1)
            return (1); // error
    }
    else if (argc == 1)
    {
        if (chdir(argv) == -1)
            printf("cd: %s: Not a dircetory\n", argv);
    }
    else
        printf("USAGE: cd [dir]\n");
    return (0);
}

int builtin_export(int argc, char *argv[], t_envp *env)
{
    //export LAN=fjk로 들어올때는 가능
    //LAN=fjk
    //export LAN으로 두번 커맨드를 작성하면 처리 불가
    t_envp *new;

    if (argc == 0)
    {
        printf("USAGE: export [KEY=VALUE]\n");
        return (1);
    }
    else
    {
        //만약 파이프 뒤에 export를 호출하면, 자식프로세스에 대한 export이므로 환경변수에 대해서 변경하지 않음
        //export하나만 들어오면 -> env 출력 : declare -x COLORTERM="truecolor" 이런식
        //export Z같은 식으로 인자가 1개만 들어오면
        //앞에  Z=jkdfls이런식의 명령어가 있으면 -> 저장
        // 아니면 환경변수에 저장되지 않음 -> error message 출력 x
        //key가 숫자만 있으면-> not a valid identifier라는 경고문구 출력
        //만약 존재하는 변수에 대해서 실행할때
        //export LANG=KOR
        //존재하는 변수를 찾아서 새로 할당하기
        //만약 존재하지 않는 변수면,
        new = make_new_node(argv[1]);
        if (new == NULL)
        {
            free_envp(env);
            return (1);
        }
        while (env->next)
            env = env->next;
        env->next = new;
    }
}

int builtin_pwd()
{
    char *buf;
    size_t size;

    buf = NULL;
    buf = getcwd(buf, size);
    if (buf == NULL)
    {
        printf("buf is null\n");
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

int builtin_unset(int argc, char *argv[], t_envp **head)
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

int builtin_env(t_envp *env)
{
    while (env)
    {
        printf("%s = %s\n", env->key, env->value);
        env = env->next;
    }
    return (0);
}

int builtin_exit(int exitcode)
{
    //exit만 입력시 -> exit출력 후 exit_success를 넘기면서 종료
    //exit뒤에 인자가 있으면, 부모에게 상태값으로 전달 -> exit출력하고 종료
    //만약 exit뒤에 인자가 두개 이상 있으면,
    //exit\n
    //bash: exit: too many arguments 
    //출력후 종료 x
    //만약 exit뒤에 숫자가 아니면,
    //exit\n
    //bash: exit: a: numeric argument required
    //출력후 종료
    //파이프 뒤에 있으면, 자식프로세스의 exit이기 때문에 쉘 종료 x
    //그러나 $?에는 해당 exit의 값이 있음
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
    builtin_pwd();
    builtin_cd(argc - 1, argv[1]);
    builtin_pwd();
    while (1) {}
    return (0);
}
