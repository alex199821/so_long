/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:03:56 by macbook           #+#    #+#             */
/*   Updated: 2024/11/14 00:26:37 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	find_rows(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			i++;
		}
	}
	return (i);
}

int	find_columns(char **map)
{
	int	rows;
	int	columns;
	int	saved_columns;

	rows = 0;
	columns = 0;
	saved_columns = 0;
	if (map)
	{
		while (map[rows])
		{
			while (map[rows][columns])
			{
				columns++;
			}
			if (saved_columns > 0 && saved_columns != columns)
			{
				return (-1);
			}
			saved_columns = columns;
			columns = 0;
			rows++;
		}
	}
	return (saved_columns);
}

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

int	validate_map(char **map)
{
	if (surrounded_walls(map, find_columns(map), find_rows(map)) < 1)
		return (0);
	if (find_columns(map) < 3 || find_rows(map) < 3)
		return (0);
	if (check_valid_path(map) < 1)
		return (0);
	return (1);
}
