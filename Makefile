# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 00:17:04 by ggeorgie          #+#    #+#              #
#    Updated: 2024/05/16 00:28:51 by ggeorgie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SOURCES = test.c \
		get_next_line.c \
		get_next_line_utils.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

# Compile each source file to an object file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

test: re
	./get_next_line input.txt
