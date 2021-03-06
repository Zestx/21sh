# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 17:44:40 by qbackaer          #+#    #+#              #
#    Updated: 2020/03/09 19:16:08 by qbackaer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra 
NAME = 21sh
INCLUDES = 21sh.h
SRCS = sources/sh21.c sources/display.c sources/input_main.c \
	   sources/input_tools.c sources/util_tab.c \
	   sources/tokens_list.c sources/tokens_tools.c \
	   sources/tokens_main.c sources/util_env.c \
	   sources/testing.c sources/tokens_split.c \
	   sources/tokens_gather.c sources/execute_main.c \
	   sources/redirect.c sources/util_pwd.c sources/cd.c \
	   sources/setenv.c
OBJS = sh21.o display.o input_main.o input_tools.o util_tab.o \
	   tokens_list.o tokens_tools.o tokens_main.o testing.o \
	   util_env.o tokens_split.o tokens_gather.o execute_main.o \
	   redirect.o util_pwd.o cd.o setenv.o

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	rm -rf ./libft/*.o
	$(CC) $(CFLAGS) $^ -I. ./libft/libft.a -o $(NAME)
	rm -rf *.o

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -I. -c $^

clean:
	rm -rf *.o
	make fclean -C ./libft

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all
