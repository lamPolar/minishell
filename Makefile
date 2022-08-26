CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS = ///
OBJS = $(SRCS:.c=.o)

NAME = minishell

token: envp.c main.c token2.c parse_util.c
	gcc $^ -lreadline -o kinder

test : test_main.c pipe.c envp.c builtin/*.c libft_util.c pipe_util.c redirect.c
	gcc $^ -lreadline -o test

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LIB)

.c.o : %.c pipe.h parse.h execute.h
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
