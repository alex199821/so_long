/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:32:37 by macbook           #+#    #+#             */
/*   Updated: 2024/11/16 03:25:51 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_wall(t_game *game, int x, int y)
{
	if (game->map[game->player_coords.y + y][game->player_coords.x
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
	if (game->map[game->player_coords.y + y][game->player_coords.x
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
	if (game->map[game->player_coords.y + y][game->player_coords.x
		+ x] == 'C')
	{
		game->map[game->player_coords.y + y][game->player_coords.x
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
		game->move_count = game->move_count + 1;
		ft_printf("Moves: %d\n", game->move_count);
		check_collectible(game, x, y);
		check_exit_possible(game, x, y);
		mlx_image_to_window(game->mlx, game->rocket, (game->player_coords.x
				+ x) * PXL, (game->player_coords.y + y) * PXL);
		if (game->map[game->player_coords.y][game->player_coords.x] != 'E')
		{
			mlx_image_to_window(game->mlx, game->background,
				(game->player_coords.x) * PXL, (game->player_coords.y)
				* PXL);
		}
		else
		{
			mlx_image_to_window(game->mlx, game->exit,
				(game->player_coords.x) * PXL, (game->player_coords.y)
				* PXL);
		}
		game->player_coords = (t_point){game->player_coords.x + x,
			game->player_coords.y + y};
	}
}
