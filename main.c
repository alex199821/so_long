/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:18:57 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/17 23:19:10 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ./so_long maps/map.ber

#include "so_long.h"

t_game	*initialize_game_data(char *argv)
{
	t_game	*game;

	game = malloc(1 * sizeof(t_game));
	if (!game)
		exit(EXIT_FAILURE);
	game->map = create_map(argv);
	game->rows = find_rows(game->map);
	game->columns = find_columns(game->map);
	game->total_collectibles = 0;
	game->collectibles_collected = 0;
	game->move_count = 0;
	game->player_coords = find_coordinates(game->map, 'P');
	game->mlx = mlx_init(PXL * game->columns, PXL * game->rows,
			"Trip to Magrathea", true);
	if (!game->mlx)
	{
		free_arofar(game->map, game->rows);
		free(game);
		exit(EXIT_FAILURE);
	}
	add_assets(game);
	return (game);
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

// void	leaks(void)
// {
// 	system("leaks so_long");
// }
// atexit(leaks);

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc == 2)
	{
		game = initialize_game_data(argv[1]);
		launch_game(game);
	}
	else
	{
		write(1, "Error\nMore than 1 Argument Entered\n", 35);
		return (1);
	}
	return (0);
}
