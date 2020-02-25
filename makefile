# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 17:44:40 by qbackaer          #+#    #+#              #
#    Updated: 2020/02/19 19:28:33 by qbackaer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -g
NAME = 21sh
INCLUDES = 21sh.h
SRCS = sources/tosh.c sources/display.c sources/input.c sources/input_tools.c \
	   sources/lex_tools.c sources/lex_ll.c sources/get_tokens.c \
	   sources/tokenize.c sources/tokenize_tools.c sources/util_env.c \
	   sources/split_commands.c sources/execute_pipeline.c \
	   sources/redirect_parse.c sources/redirect_apply.c
OBJS = tosh.o display.o input.o input_tools.o lex_tools.o lex_ll.o \
	   tokenize.o tokenize_tools.o util_env.o get_tokens.o \
	   split_commands.o execute_pipeline.o redirect_parse.o \
	   redirect_apply.o

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
