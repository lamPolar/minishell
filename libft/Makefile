# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 00:41:31 by heeskim           #+#    #+#              #
#    Updated: 2022/07/01 17:32:05 by heeskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
SRCS = ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isascii.c ft_isprint.c \
	   ft_toupper.c ft_tolower.c \
	   ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	   ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	   ft_strncmp.c ft_strnstr.c ft_strlen.c ft_strdup.c \
	   ft_atoi.c ft_calloc.c \
	   ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		  	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
NAME = libft.a
.SUFFIXES : .c .o
.PHONY : all fclean clean bonus re 

all : $(NAME)
$(NAME) : $(OBJS)
	ar rcs $@ $?
%.o : %.c libft.h
	$(CC) $(CFLAGS) $< -o $@
clean :
	rm -f $(OBJS) $(BONUS_OBJS) 
fclean : 
	make clean
	rm -f $(NAME)
bonus :
	@make "OBJS = $(OBJS) $(BONUS_OBJS)" all
re : fclean all
