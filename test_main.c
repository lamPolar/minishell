#include "util/util.h"
#include "define.h"
#include "parse.h"
#include "pipe.h"
#include "builtin/builtin.h"

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

int redirection_test_main(int argc, char *argv[])
{
    write(1,ft_strjoin_three("abc", "bcd", "jdksla\n"), 14);
    here_doc(STDOUT_FILENO, argv[1]);
}

// t_node *make_new_node(char *str, int type, t_node *papa)
// {
//     t_node *new;

//     new = (t_node *)ft_calloc(sizeof(t_node), 1);
//     if (new == NULL)
//         return (NULL);
//     new->str = str;
//     new->type = type;
//     new->right = NULL;
//     new->left = NULL;
//     new->papa = papa;
//     return (new);
// }

//전위순회 방법 
//preorder way 
void	preorder(t_node *root)
{
	printf("str : %s ", root->str);
	printf("type : %d \n", root->type);
	if(root->left)
		preorder(root->left);
	if (root->right)
		preorder(root->right);
}

int builtin_main(int argc, char *argv[], char *envp[])
{
    //preorder(head);
    
    // builtin_env(env);
    // printf("\n\n");
    // if (ft_strequal(head_right->right->str, "export"))
    //     builtin_export(head_right->right, env);
    // printf("\n\n");
    // builtin_env(env);
    // printf("\n\n");
    // if (ft_strequal(left_right->str, "unset"))
    //     builtin_unset(left_right, env);
    // printf("\n\n");
    // builtin_env(env);  

    // builtin_env(env);
    // printf("\n\n");
    // if (ft_strequal(left_right->str, "export"))
    //     builtin_export(left_right, env);
    // printf("\n\n");    
    // builtin_env(env);  

    // if (ft_strequal(left_right->str, "env"))
    //     builtin_env(env); 
   
    // if (ft_strequal(left_right->str, "echo"))
    //     builtin_echo(left_right, env);
   
    // if (ft_strequal(left_right->str, "cd"))
    //     builtin_cd(left_right, env);
    // builtin_pwd(head);

    // head->right = make_new_node(NULL, PIPE, head);
    // head_right = head->right;

    while (1){
    }
}


void    B(t_node *node){
    t_node *queue;


}