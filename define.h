#ifndef DEFINE_H
# define DEFINE_H

// t_node.type
# define PIPE 1
# define LINE 2
# define REDIRECTION 3
# define COMMAND 4

// redirection mode : << < > >>
# define HEREDOC 0
# define INFILE 1
# define OUTFILE 2
# define APPEND_OUT 3

// envp.display
# define HIDE 0
# define SHOW 1

typedef struct envp
{
	char		*key;
	char		*value;
	int			display;
	struct envp	*next;
}	t_envp;

typedef struct token
{
	int				type;
	char			*value;
	struct token	*next;
}	t_token;

typedef struct node
{
	struct node	*left;
	struct node	*right;
	struct node	*papa;
	char		*str;
	int			type;
}	t_node;

#endif