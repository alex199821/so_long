/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:44:36 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/17 22:39:16 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define PXL 48

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
	int			move_count;
	int			rows;
	int			columns;
	int			total_collectibles;
	int			collectibles_collected;
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
int				find_columns(char **map);
int				check_valid_path(char **map);
t_point			find_coordinates(char **map, char point);
// validate.c
int				validate_map(char **map);
int				find_rows(char **map);
// map.c
char			**initialize_map(char *argv);
char			**create_map(char *argv);
void			add_assets(t_game *game);
void			flood_map_background(t_game *game);
void			flood_map_items(t_game *game);
// map_utils.c
char			*join_str(char *buffer, char *tmp);
void			print_arofars(char **ar);
char			**free_arofar(char **parentarray, int arrayindex);
int				check_for_double_nl(char *string);
// movement.c
int				check_wall(t_game *game, int x, int y);
int				check_exit_possible(t_game *game, int x, int y);
int				check_collectible(t_game *game, int x, int y);
void			move(t_game *game, int x, int y);

#endif