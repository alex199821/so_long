/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:44:36 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/15 02:10:22 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define IMG_PIXEL 48

# include "./MLX42/include/MLX42/MLX42.h"
# include "lib/lib.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	int			rows;
	int			columns;
	t_point		player_coords;
	mlx_image_t	*background;
	mlx_image_t	*rocket;
	mlx_image_t	*exit;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
}				t_game;

// main.c
char			**free_arofar(char **parentarray, int arrayindex);
// valid_path.c
int				check_valid_path(char **map);
// validate.c
int				validate_map(char **map);
int				find_rows(char **map);
int				find_columns(char **map);

#endif