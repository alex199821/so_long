# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbook <macbook@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 02:17:11 by macbook           #+#    #+#              #
#    Updated: 2024/11/13 02:24:14 by macbook          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = lib.a

GNL_DIR = ./get_next_line

GNLSRCS = get_next_line.c get_next_line_utils.c

GNLOBJS = $(addprefix $(GNL_DIR)/, $(GNLSRCS:.c=.o))

OBJS = $(GNLOBJS)

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