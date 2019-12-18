# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 17:44:40 by qbackaer          #+#    #+#              #
#    Updated: 2019/12/18 18:23:56 by qbackaer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -g
NAME = 21sh
INCLUDES = 21sh.h
SRCS = 21sh.c lex_main.c lex_tools.c lex_ll.c 
OBJS = 21sh.o lex_main.o lex_tools.o lex_ll.o

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
