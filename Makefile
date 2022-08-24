0CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCS = ///
OBJS = $(SRCS:.c=.o)
LDIR = ./libft
LIB = $(LDIR)/libft.a
INCLUDE = -I $(LDIR)

NAME = pipex

all : $(NAME)
$(NAME) : $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LIB)

.c.o : %.c pipe.h parse.h execute.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIB) : 
	make -C $(LDIR) all

clean :
	make -C $(LDIR) clean
	rm -f $(OBJS)

fclean : 
	make clean
	make -C $(LDIR) fclean
	rm -f $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re
