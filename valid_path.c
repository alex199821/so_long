/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:06:53 by macbook           #+#    #+#             */
/*   Updated: 2024/11/16 02:39:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	find_coordinates(char **map, char point)
{
	int		rows;
	int		columns;
	t_point	coordinates;

	rows = 0;
	coordinates.x = -1;
	coordinates.y = -1;
	while (map[rows])
	{
		columns = 0;
		while (map[rows][columns])
		{
			if (map[rows][columns] == point)
			{
				coordinates.y = rows;
				coordinates.x = columns;
				return (coordinates);
			}
			columns++;
		}
		rows++;
	}
	return (coordinates);
}

char	**copy_map(char **map, int rows)
{
	char	**map_copy;
	int		i;

	i = 0;
	map_copy = (char **)malloc((rows + 1) * sizeof(char *));
	if (!map_copy)
		return (NULL);
	while (i < rows)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (map_copy[i] == NULL)
			return (free_arofar(map_copy, i));
		i++;
	}
	return (map_copy);
}

int	check_path(char **map, int rows, int cols, t_point cur)
{
	if (cur.y < 0 || cur.y >= rows || cur.x < 0 || cur.x >= cols)
		return (0);
	if (map[cur.y][cur.x] == '1' || map[cur.y][cur.x] == 'V')
		return (0);
	if (map[cur.y][cur.x] == 'E')
		return (1);
	map[cur.y][cur.x] = 'V';
	if (check_path(map, rows, cols, (t_point){cur.x - 1, cur.y})
		|| check_path(map, rows, cols, (t_point){cur.x + 1, cur.y})
		|| check_path(map, rows, cols, (t_point){cur.x, cur.y - 1})
		|| check_path(map, rows, cols, (t_point){cur.x, cur.y + 1}))
	{
		return (1);
	}
	return (0);
}

int	check_valid_path(char **map)
{
	t_point	player_coords;
	char	**map_copy;
	int		exit_found;
	int		rows;
	int		columns;

	rows = find_rows(map);
	columns = find_columns(map);
	map_copy = copy_map(map, rows);
	player_coords = find_coordinates(map, 'P');
	exit_found = check_path(map_copy, rows, columns, player_coords);
	free_arofar(map_copy, rows);
	return (exit_found);
}
