/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:25:04 by macbook           #+#    #+#             */
/*   Updated: 2024/11/17 23:17:09 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

char	**initialize_map(char *argv)
{
	int		fd;
	char	*line;
	char	*array;
	char	**map;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (write(1, "Error\nFile N/A\n", 15), exit(EXIT_FAILURE), NULL);
	array = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		array = join_str(array, line);
		if (line != NULL)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (check_for_double_nl(array))
		return (write(1,
				"Error\nYour map contains multiple New Lines in a Row\n", 53),
			free(array), exit(1), NULL);
	map = ft_split(array, '\n');
	free(array);
	return (map);
}

char	**create_map(char *argv)
{
	char	**map;

	map = initialize_map(argv);
	if (!validate_map(map))
	{
		free_arofar(map, find_rows(map));
		exit(EXIT_FAILURE);
	}
	return (map);
}

void	add_assets(t_game *game)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png("./textures/background.png");
	img = mlx_texture_to_image(game->mlx, texture);
	game->background = img;
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/ship.png");
	img = mlx_texture_to_image(game->mlx, texture);
	game->rocket = img;
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/exit.png");
	img = mlx_texture_to_image(game->mlx, texture);
	game->exit = img;
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/asteroid.png");
	img = mlx_texture_to_image(game->mlx, texture);
	game->wall = img;
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/planet.png");
	img = mlx_texture_to_image(game->mlx, texture);
	game->collectible = img;
	mlx_delete_texture(texture);
}

void	flood_map_background(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->columns)
		{
			mlx_image_to_window(game->mlx, game->background, x * PXL, y * PXL);
			x++;
		}
		y++;
	}
}

void	flood_map_items(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->columns)
		{
			if (game->map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->wall, x * PXL, y * PXL);
			if (game->map[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->exit, x * PXL, y * PXL);
			if (game->map[y][x] == 'P')
				mlx_image_to_window(game->mlx, game->rocket, x * PXL, y * PXL);
			if (game->map[y][x] == 'C')
			{
				mlx_image_to_window(game->mlx, game->collectible, x * PXL, y
					* PXL);
				game->total_collectibles = game->total_collectibles + 1;
			}
			x++;
		}
		y++;
	}
}
