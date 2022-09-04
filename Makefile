CC = gcc
CFLAGS = -Wall -Werror -Wextra
PARSE = parse/into_ast.c parse/token_after.c \
		parse/token_env.c parse/token_find.c parse/token_what.c \
		parse/token.c parse/make_ast.c
UTIL = 	util/ast_util.c util/builtin_util.c util/envp_util.c \
		util/envp_util2.c util/libft_util.c util/libft_util2.c \
		util/libft_util3.c util/parse_util.c util/parse_util2.c \
		util/pipe_util.c util/pipe_util2.c util/pipe_util3.c \
		util/pipe_util4.c util/split_util.c
BUILTIN = 	builtin/builtin_cd.c builtin/builtin_echo.c \
			builtin/builtin_env.c builtin/builtin_export.c \
			builtin/builtin.c
EXECUTE = execute/execute.c execute/execute2.c execute/pipe.c \
			execute/redirect.c execute/signal.c
SRCS = $(PARSE) $(UTIL) $(BUILTIN) $(EXECUTE) main.c
OBJS = $(SRCS:.c=.o)
LIBS = define.h util/util.h execute/pipe.h parse/parse.h builtin/builtin.h
NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $^ -lreadline -L/usr/local/opt/readline/lib -o $(NAME)
	@printf "\n\e[0;32m$(NAME) was created successfully. \e[0m\n"

.c.o : %.c $(LIBS)
	@$(CC) $(CFLAGS) -I/usr/local/opt/readline/include -c $< -o $@
	@printf "\e[1;32m██\e[0m"

clean :
	@rm -f $(OBJS)
	@printf "$(NAME)'s object files were removed successfully.\n"

fclean : 
	@make clean
	@rm -f $(NAME)
	@printf "$(NAME) was removed successfully.\n\n"

re : 
	@make fclean
	@make all

.PHONY : all clean fclean re
