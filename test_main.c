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

int main(int argc, char *argv[], char *envp[])
{
    t_node *head;
    t_node *head_left;
    t_node *left_left;
    t_node *left_right;
    t_node *head_right;
    t_envp *env;

    env = arrange_envp(envp);
    head = make_new_node(NULL, PIPE, NULL);
    head->left = make_new_node(NULL, LINE, head);
    head_left = head->left;

    head_left->left = make_new_node(("<<"), REDIRECTION, head_left);
    left_left = head_left->left;
    left_left->left = make_new_node(("a"), REDIRECTION, left_left);
    left_left->right = make_new_node((">"), REDIRECTION, left_left);
    left_left->right->left = make_new_node(("b"), REDIRECTION, left_left->right);

    head_left->right = make_new_node(("cd"), COMMAND, head_left);
    left_right = head_left->right;
    left_right->right = make_new_node(("~"), COMMAND, left_right);
    // left_right->right->right = make_new_node(("LESS"), COMMAND, left_right->right);
    // left_right->right->right->right = make_new_node(("o"), COMMAND, left_right->right->right);
    ///left_right->right->right->right->right = make_new_node(("..."), COMMAND, left_right->right->right->right);

    head->right = make_new_node(NULL, LINE, head);
    head_right = head->right;
    head_right->right = make_new_node("export", COMMAND, head_right);
    head_right->right->right = make_new_node("ABC=ABC", COMMAND, head_right->right);
    
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
   
    if (ft_strequal(left_right->str, "cd"))
        builtin_cd(left_right, env);
    builtin_pwd(head);
    // head->right = make_new_node(NULL, PIPE, head);
    // head_right = head->right;
}
