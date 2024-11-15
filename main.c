/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:18:57 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/15 21:09:00 by auplisas         ###   ########.fr       */
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

int	check_for_double_nl(char *string)
{
	int	i;

	if (string == NULL)
		return (0);
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\n' && string[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
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
	if (check_for_double_nl(array))
	{
		write(1, "Error\n", 6);
		write(1, "Your map contains multiple New Lines in a Row\n", 47);
		free(array);
		exit(1);
	}
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
			// if (game->map[y][x] == 'L')
			// 	mlx_image_to_window(game->mlx, game->background, x * PXL, y
			// 		* PXL);
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
	game->total_collectibles = 0;
	game->collectibles_collected = 0;
	game->player_coordinates = find_coordinates(game->map, 'P');
	game->mlx = mlx_init(PXL * game->columns, PXL * game->rows,
			"Trip to Magrathea", false);
	// if (!game->mlx)
	// 	return (NULL);
	add_assets(game);
	return (game);
}

int	check_wall(t_game *game, int x, int y)
{
	if (game->map[game->player_coordinates.y + y][game->player_coordinates.x
		+ x] == '1')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	check_exit_possible(t_game *game, int x, int y)
{
	if (game->map[game->player_coordinates.y + y][game->player_coordinates.x
		+ x] == 'E' && game->total_collectibles == game->collectibles_collected)
	{
		mlx_close_window(game->mlx);
		return (1);
	}
	else
	{
		return (0);
	}
}

int	check_collectible(t_game *game, int x, int y)
{
	if (game->map[game->player_coordinates.y + y][game->player_coordinates.x
		+ x] == 'C')
	{
		game->map[game->player_coordinates.y + y][game->player_coordinates.x
			+ x] = '0';
		game->collectibles_collected = game->collectibles_collected + 1;
		return (1);
	}
	else
	{
		return (0);
	}
}

void	move(t_game *game, int x, int y)
{
	if (check_wall(game, x, y) == 0)
	{
		// if (x == 0 && y == -1)
		// 	write(1, "UP\n", 3);
		// if (x == 0 && y == 1)
		// 	write(1, "DOWN\n", 5);
		// if (x == -1 && y == 0)
		// 	write(1, "LEFT\n", 5);
		// if (x == 1 && y == 0)
		// 	write(1, "RIGHT\n", 6);
		check_collectible(game, x, y);
		check_exit_possible(game, x, y);
		mlx_image_to_window(game->mlx, game->rocket, (game->player_coordinates.x
				+ x) * PXL, (game->player_coordinates.y + y) * PXL);
		if (game->map[game->player_coordinates.y][game->player_coordinates.x] != 'E')
		{
			mlx_image_to_window(game->mlx, game->background,
				(game->player_coordinates.x) * PXL, (game->player_coordinates.y)
				* PXL);
		}
		else
		{
			mlx_image_to_window(game->mlx, game->exit,
				(game->player_coordinates.x) * PXL, (game->player_coordinates.y)
				* PXL);
		}
		game->player_coordinates = (t_point){game->player_coordinates.x + x,
			game->player_coordinates.y + y};
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move(game, 0, -1);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move(game, 0, 1);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move(game, -1, 0);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move(game, 1, 0);
}

int	launch_game(t_game *game)
{
	flood_map_background(game);
	flood_map_items(game);
	mlx_key_hook(game->mlx, my_keyhook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_arofar(game->map, find_rows(game->map));
	free(game);
	return (0);
}

void	leaks(void)
{
	system("leaks so_long");
}

int	main(void)
{
	t_game	*game;

	// atexit(leaks);
	game = initialize_game_data();
	launch_game(game);
	return (0);
}
