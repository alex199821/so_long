# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 18:31:36 by auplisas          #+#    #+#              #
#    Updated: 2024/11/12 21:48:04 by auplisas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra
USER = $(shell whoami)
MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
MAKE_LIB = ar -rcs

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: MLX42 $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) ./MLX42/build/libmlx42.a $(MLXFLAGS)

MLX42:
	@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build && cmake --build build -j4

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C 

clean:
	rm -rf MLX42
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re