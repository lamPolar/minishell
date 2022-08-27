CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS = ///
OBJS = $(SRCS:.c=.o)

NAME = minishell

token: parse/*.c util/*.c main.c
	gcc $^ -lreadline -o kinder

test : main.c pipe.c redirect.c execute.c builtin/*.c util/*.c parse/*.c
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
