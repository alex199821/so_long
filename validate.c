/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:03:56 by macbook           #+#    #+#             */
/*   Updated: 2024/11/18 02:09:37 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	surrounded_walls(char **map, int cols, int rows)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0 && map[i][j] != '1')
				return (0);
			if (j == 0 && map[i][j] != '1')
				return (0);
			if (i == rows - 1 && map[i][j] != '1')
				return (0);
			if (j == cols - 1 && map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	collectible_exists(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_player_and_exit(char **map, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
			{
				count++;
			}
			j++;
		}
		i++;
	}
	if (count > 1)
		return (1);
	else
		return (0);
}

int	check_for_invalid_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_character(map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(char **map)
{
	if (surrounded_walls(map, find_columns(map), find_rows(map)) < 1)
		return (write(1, "Error\n", 6), write(1,
				"Your Map is Not Surrounded by Walls\n", 36), 0);
	if (find_columns(map) < 3 || find_rows(map) < 3)
		return (write(1, "Error\n", 6), write(1,
				"Your Map is Not a Rectangle\n", 28), 0);
	if (check_valid_path(map) < 1)
		return (write(1, "Error\n", 6), write(1, "Player Unable to Exit\n", 22),
			0);
	if (collectible_exists(map) < 1)
		return (write(1, "Error\n", 6), write(1, "No collectible on the Map\n",
				26), 0);
	if (check_player_and_exit(map, 'E') || check_player_and_exit(map, 'P'))
		return (write(1, "Error\n", 6), write(1,
				"Map Contains Duplicate Characters\n", 34), 0);
	if (check_for_invalid_chars(map) > 0)
		return (write(1, "Error\n", 6), write(1, "Map Contains Invalid Chars\n",
				27), 0);
	return (1);
}
