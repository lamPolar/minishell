CC = gcc
CFLAGS = -Wall -Werror -Wextra
PARSE = parse/envp.c parse/into_ast.c parse/token_after.c \
		parse/token_env.c parse/token_find.c parse/token_what.c \
		parse/token.c parse/make_ast.c
UTIL = 	util/ast_util.c util/builtin_util.c util/envp_util.c \
		util/libft_util.c util/parse_util.c util/pipe_util.c
BUILTIN = 	builtin/builtin_cd.c builtin/builtin_echo.c \
			builtin/builtin_env.c builtin/builtin_export.c \
			builtin/builtin.c
SRCS = $(PARSE) $(UTIL) $(BUILTIN) execute.c main.c pipe.c redirect.c
OBJS = $(SRCS:.c=.o)
LIBS = pipe.h define.h parse/parse.h builtin/builtin.h util/util.h
NAME = minishell

#token: parse/*.c util/*.c main.c
#	gcc $^ -lreadline -o kinder

#test : main.c pipe.c redirect.c execute.c builtin/*.c util/*.c parse/*.c
#gcc -g $^ -lreadline -o test

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -lreadline -o $(NAME)

.c.o : %.c $(LIBS)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : 
	make clean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re
