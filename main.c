/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:18:57 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/15 03:47:13 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ./so_long maps/map.ber

#include "so_long.h"

char	*join_str(char *buffer, char *tmp)
{
	char	*str;

	str = ft_strjoin(buffer, tmp);
	free(buffer);
	return (str);
}

void	print_arofars(char **ar)
{
	int	i;

	if (ar)
	{
		i = 0;
		while (ar[i])
		{
			printf("Row [%d] = %s\n", i, ar[i]);
			i++;
		}
	}
}

char	**free_arofar(char **parentarray, int arrayindex)
{
	int	j;

	j = 0;
	while (j < arrayindex)
	{
		free(parentarray[j]);
		j++;
	}
	free(parentarray);
	return (NULL);
}

char	**initialize_map(void)
{
	int		fd;
	char	*line;
	char	*array;
	char	**map;

	fd = open("maps/map.ber", O_RDONLY);
	if (fd < 0)
		return (NULL);
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
	map = ft_split(array, '\n');
	free(array);
	return (map);
}

char	**create_map(void)
{
	char	**map;

	map = initialize_map();
	if (!validate_map(map))
	{
		free_arofar(map, find_rows(map));
		write(1, "Error\n", 6);
		return (NULL);
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
			mlx_image_to_window(game->mlx, game->background, x * IMG_PIXEL, y
				* IMG_PIXEL);
			x++;
		}
		y++;
	}
}

// void clean_map(t_game *game)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < game->rows)
// 	{
// 		x = 0;
// 		while (x < game->columns)
// 		{
			
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
			{
				mlx_image_to_window(game->mlx, game->wall, x * IMG_PIXEL, y
					* IMG_PIXEL);
			}
			if (game->map[y][x] == 'E')
			{
				mlx_image_to_window(game->mlx, game->exit, x * IMG_PIXEL, y
					* IMG_PIXEL);
			}
			if (game->map[y][x] == 'P')
			{
				mlx_image_to_window(game->mlx, game->rocket, x * IMG_PIXEL, y
					* IMG_PIXEL);
			}
			if (game->map[y][x] == 'C')
			{
				mlx_image_to_window(game->mlx, game->collectible, x * IMG_PIXEL,
					y * IMG_PIXEL);
			}
			if (game->map[y][x] == 'L')
			{
				mlx_image_to_window(game->mlx, game->background, x * IMG_PIXEL,
					y * IMG_PIXEL);
			}
			x++;
		}
		y++;
	}
}

t_game	*initialize_game_data(void)
{
	t_game	*game;

	game = malloc(1 * sizeof(t_game));
	// if (!game)
	// 	return (NULL);
	game->map = create_map();
	// if (!game->map)
	// 	return (NULL);
	game->rows = find_rows(game->map);
	game->columns = find_columns(game->map);
	game->player_coordinates = find_coordinates(game->map, 'P');
	game->mlx = mlx_init(IMG_PIXEL * 34, IMG_PIXEL * 6, "Trip to Magrathea",
			false);
	// if (!game->mlx)
	// 	return (NULL);
	add_assets(game);
	return (game);
}

// void	ft_hook(void *param)
// {
// 	t_game	*game;

// 	game = param;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
// 	{
// 		mlx_close_window(game->mlx);
// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
// 	{
// 		write(1, "UP", 2);
// 		// game->map[0][0] = 'E';
// 		// flood_map_items(game);
// 		// image->instances[0].y -= 5;
// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
// 	{
// 		write(1, "DOWN", 4);
// 		// image->instances[0].y += 5;
// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
// 	{
// 		write(1, "LEFT", 4);
// 		game->map[game->player_coordinates.y][game->player_coordinates.x - 1] = 'P';
// 		game->map[game->player_coordinates.y][game->player_coordinates.x] = 'L';
// 		game->player_coordinates = (t_point){game->player_coordinates.x - 1, game->player_coordinates.y};
// 				flood_map_items(game);

// 	}
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
// 	{
// 		write(1, "RIGHT", 5);
// 		// mlx_image_to_window(game->mlx, game->background, 1 * IMG_PIXEL, 4
// 		// 	* IMG_PIXEL);
// 		game->map[game->player_coordinates.y][game->player_coordinates.x + 1] = 'P';
// 		game->map[game->player_coordinates.y][game->player_coordinates.x] = 'L';
// 		game->player_coordinates = (t_point){game->player_coordinates.x + 1, game->player_coordinates.y};

// 		// game->player_coordinates = (t_point){game->player_coordinates.x + 1,
// 		// 	game->player_coordinates.y};
// 		print_arofars(game->map);
// 		flood_map_items(game);
// 		// mlx_image_to_window(game->mlx, game->rocket, 2 * IMG_PIXEL, 4
// 		// 	* IMG_PIXEL);
// 		// image->instances[0].x += 5;
// 	}
// }

void	my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(game->mlx);
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		write(1, "UP", 2);
		// game->map[0][0] = 'E';
		// flood_map_items(game);
		// image->instances[0].y -= 5;
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		write(1, "DOWN", 4);
		// image->instances[0].y += 5;
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		write(1, "LEFT", 4);
		game->map[game->player_coordinates.y][game->player_coordinates.x - 1] = 'P';
		game->map[game->player_coordinates.y][game->player_coordinates.x] = 'L';
		game->player_coordinates = (t_point){game->player_coordinates.x - 1, game->player_coordinates.y};
				flood_map_items(game);

	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		write(1, "RIGHT", 5);
		// mlx_image_to_window(game->mlx, game->background, 1 * IMG_PIXEL, 4
		// 	* IMG_PIXEL);
		game->map[game->player_coordinates.y][game->player_coordinates.x + 1] = 'P';
		game->map[game->player_coordinates.y][game->player_coordinates.x] = 'L';
		game->player_coordinates = (t_point){game->player_coordinates.x + 1, game->player_coordinates.y};

		// game->player_coordinates = (t_point){game->player_coordinates.x + 1,
		// 	game->player_coordinates.y};
		print_arofars(game->map);
		flood_map_items(game);
		// mlx_image_to_window(game->mlx, game->rocket, 2 * IMG_PIXEL, 4
		// 	* IMG_PIXEL);
		// image->instances[0].x += 5;
	}
}

int	launch_game(t_game *game)
{
	flood_map_background(game);
	flood_map_items(game);
	mlx_key_hook(game->mlx, my_keyhook, game);
	// mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_arofar(game->map, find_rows(game->map));
	free(game);
	return (0);
}

int	main(void)
{
	t_game	*game;

	game = initialize_game_data();
	launch_game(game);
	return (0);
}