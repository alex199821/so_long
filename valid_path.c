/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:06:53 by macbook           #+#    #+#             */
/*   Updated: 2024/11/18 03:49:53 by auplisas         ###   ########.fr       */
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

int	check_collectibles_path(char **map, int rows, int cols, t_point cur)
{
	int	collectibles_found;

	collectibles_found = 0;
	if (cur.y < 0 || cur.y >= rows || cur.x < 0 || cur.x >= cols)
		return (0);
	if (map[cur.y][cur.x] == '1' || map[cur.y][cur.x] == 'V')
		return (0);
	if (map[cur.y][cur.x] == 'C')
		collectibles_found = 1;
	map[cur.y][cur.x] = 'V';
	collectibles_found += check_collectibles_path(map, rows, cols,
			(t_point){cur.x - 1, cur.y});
	collectibles_found += check_collectibles_path(map, rows, cols,
			(t_point){cur.x + 1, cur.y});
	collectibles_found += check_collectibles_path(map, rows, cols,
			(t_point){cur.x, cur.y - 1});
	collectibles_found += check_collectibles_path(map, rows, cols,
			(t_point){cur.x, cur.y + 1});
	return (collectibles_found);
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
	player_coords = find_coordinates(map, 'P');
	map_copy = copy_map(map, rows);
	exit_found = check_path(map_copy, rows, columns, player_coords);
	free_arofar(map_copy, rows);
	map_copy = copy_map(map, rows);
	if (count_collectibles(map) != check_collectibles_path(map_copy, rows,
			columns, player_coords))
		exit_found = 0;
	free_arofar(map_copy, rows);
	return (exit_found);
}
