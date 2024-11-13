/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:18:57 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/13 22:48:42 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://cdn.intra.42.fr/pdf/pdf/135147/en.subject.pdf
// https://gvituri.itch.io/space-shooter/download/eyJpZCI6OTk4MTA4LCJleHBpcmVzIjoxNzMxNDQ2MTQwfQ%3d%3d.fEuG8GFMtC2%2bqPmZfUNm2T%2bUifk%3d
// ./so_long maps/map.ber
#include "so_long.h"
#include <stdio.h>
#include <unistd.h>

#define WIDTH 1024
#define HEIGHT 512

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

char	**frees_all(char **parentarray, int arrayindex)
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

// char	**initialize_map(void)
// {
// 	int		fd;
// 	char	*line;
// 	char	*array;
// 	char	**map;

// 	fd = open("maps/map.ber", O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	array = ft_strdup("");
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		array = join_str(array, line);
// 		line = get_next_line(fd);
// 	}

// 	close(fd);
// 	map = ft_split(array, '\n');
// 	free(array);
// 	return (map);
// }

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
	if (!array)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("Line is: %s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map = ft_split(array, '\n');
	free(line);
	free(array);
	return (map);
}

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

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

t_point	find_coordinates(char **map, char point)
{
	int		rows;
	int		columns;
	t_point	coordinates;

	rows = 0;
	coordinates.x = -1;
	coordinates.y = -1;
	if (map)
	{
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
	}
	return (coordinates);
}

char	**copy_map(char **map, int rows)
{
	char	**map_copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map_copy = (char **)malloc((rows + 1) * sizeof(char *));
	if (!map_copy)
		return (NULL);
	while (i < rows)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (map_copy[i] == NULL)
			return (frees_all(map_copy, i));
		i++;
	}
	return (map_copy);
}

int	check_path(char **map, int rows, int cols, t_point cur, char exit)
{
	if (cur.y < 0 || cur.y >= rows || cur.x < 0 || cur.x >= cols)
		return (0);
	if (map[cur.y][cur.x] == '1' || map[cur.y][cur.x] == 'V')
		return (0);
	if (map[cur.y][cur.x] == exit)
		return (1);
	map[cur.y][cur.x] = 'V';
	if (check_path(map, rows, cols, (t_point){cur.x - 1, cur.y}, exit)
		|| check_path(map, rows, cols, (t_point){cur.x + 1, cur.y}, exit)
		|| check_path(map, rows, cols, (t_point){cur.x, cur.y - 1}, exit)
		|| check_path(map, rows, cols, (t_point){cur.x, cur.y + 1}, exit))
	{
		return (1);
	}
	return (0);
}

int	check_valid_path(char **map)
{
	t_point	player_coordinates;
	char	**map_copy;
	int		exit_found;

	map_copy = copy_map(map, find_rows(map));
	player_coordinates = find_coordinates(map, 'P');
	exit_found = check_path(map_copy, find_rows(map_copy),
			find_columns(map_copy), player_coordinates, 'E');
	frees_all(map_copy, find_rows(map));
	return (exit_found);
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

void	leaks(void)
{
	system("leaks so_long");
}

int32_t	main(void)
{
	char	**map;

	atexit(leaks);
	map = initialize_map();
	validate_map(map);
	if (!validate_map(map))
	{
		frees_all(map, find_rows(map));
		write(1, "Error\n", 6);
		return (0);
	}
	print_arofars(map);
	frees_all(map, find_rows(map));
	// mlx_t			*mlx;
	// mlx_texture_t	*texture;
	// mlx_texture_t	*asteroid;
	// mlx_image_t		*img;
	// mlx_image_t		*asteroid_img;
	// // Start mlx
	// mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	// if (!mlx)
	// 	error();
	// // Load the texture
	// texture = mlx_load_png("./textures/background.png");
	// if (!texture)
	// 	error();
	// // Load the asteroid
	// asteroid = mlx_load_png("./textures/asteroid.png");
	// if (!texture)
	// 	error();
	// // Convert texture to an image
	// img = mlx_texture_to_image(mlx, texture);
	// if (!img)
	// 	error();
	// // Convert asteroid texture to img
	// asteroid_img = mlx_texture_to_image(mlx, asteroid);
	// if (!asteroid_img)
	// 	error();
	// // Tile the background
	// for (int y = 0; y < HEIGHT; y += img->height)
	// {
	// 	for (int x = 0; x < WIDTH; x += img->width)
	// 	{
	// 		if (mlx_image_to_window(mlx, img, x, y) < 0)
	// 			error();
	// 	}
	// }
	// // place the asteroid
	// if (mlx_image_to_window(mlx, asteroid_img, 0, 0) < 0)
	// 	error();
	// mlx_loop(mlx);
	// // Clean up
	// mlx_delete_image(mlx, img);
	// mlx_delete_texture(texture);
	// mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
// #define WIDTH 512
// #define HEIGHT 512

// static mlx_image_t	*image;

//
// -----------------------------------------------------------------------------

// int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

// void	ft_randomize(void *param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(rand() % 0xFF, // R
// 										rand() % 0xFF, // G
// 										rand() % 0xFF, // B
// 										rand() % 0xFF  // A
// 			);
// 			mlx_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void	ft_hook(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

//
// -----------------------------------------------------------------------------

// int	main(void)
// {
// 	mlx_t	*mlx;
// 	// int		fd;
// 	// char	*line;
// 	// int		i;

// 	// i = 0;
// 	// fd = open("maps/map.ber", O_RDONLY);
// 	// if (fd < 0)
// 	// {
// 	// 	perror("Error opening file");
// 	// 	return (1);
// 	// }
// 	// while ((line = get_next_line(fd)) != NULL && i < 20)
// 	// {
// 	// 	i++;
// 	// 	printf("Read Line: %s", line);
// 	// }
// 	// close(fd);
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return (1);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return (1);
// 	}
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return (1);
// 	}
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (0);
// }
