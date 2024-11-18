# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 18:31:36 by auplisas          #+#    #+#              #
#    Updated: 2024/11/18 02:37:29 by auplisas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
CFLAGS = -Wall -Werror -Wextra
USER = $(shell whoami)
MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
MAKE_LIB = ar -rcs

SRCS = 	main.c \
		map_utils.c \
		map_utils_2.c \
		map.c \
		movement.c \
		valid_path.c \
		validate.c \
				
OBJS = $(SRCS:.c=.o)

all: MLX42 $(NAME)

$(NAME): $(OBJS)
	@cd lib && make --silent
	$(CC) $(CFLAGS) -o $@ $(OBJS) ./lib/lib.a ./MLX42/build/libmlx42.a $(MLXFLAGS)

MLX42:
	@if [ ! -d "MLX42" ]; then git clone https://github.com/codam-coding-college/MLX42.git; fi
	@cd MLX42 && cmake -B build && cmake --build build -j4

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C 

clean:
	rm -rf MLX42
	cd lib && make clean
	rm -f $(OBJS)
	rm -f lib/lib.a

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re