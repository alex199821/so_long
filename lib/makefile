# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbook <macbook@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 02:17:11 by macbook           #+#    #+#              #
#    Updated: 2024/11/13 03:48:43 by macbook          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = lib.a

GET_NEXT_LINE_DIR = ./get_next_line

GET_NEXT_LINE_SRCS = get_next_line.c get_next_line_utils.c

GET_NEXT_LINE_OBJS = $(addprefix $(GET_NEXT_LINE_DIR)/, $(GET_NEXT_LINE_SRCS:.c=.o))

OBJS = $(GET_NEXT_LINE_OBJS)

OBJDIR = ./objs

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re