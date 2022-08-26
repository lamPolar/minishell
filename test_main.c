#include "parse.h"
#include "pipe.h"

int print_envp(char *envp[])
{
    t_envp *env;
    char **reenvp;
    int i;

    env = arrange_envp(envp);
    reenvp = dearrange_envp(env);
    i = 0;
    while (reenvp[i])
    {
        printf("%s\n", reenvp[i]);
        i++;
    }
}

int main(void)
{
    write(1,ft_strjoin_three("abc", "bcd", "jdksla"), 13);
}