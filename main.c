/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:18:57 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/13 14:22:05 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://cdn.intra.42.fr/pdf/pdf/135147/en.subject.pdf
// https://gvituri.itch.io/space-shooter/download/eyJpZCI6OTk4MTA4LCJleHBpcmVzIjoxNzMxNDQ2MTQwfQ%3d%3d.fEuG8GFMtC2%2bqPmZfUNm2T%2bUifk%3d
// ./so_long maps/map.ber
#include "so_long.h"
#include <stdio.h>

////LINKED LIST MAP////////

// size_t	ft_strlensd(const char *c)
// {
// 	size_t	i;

// 	i = 0;
// 	while (c[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

t_map	*create_node(char *line)
{
	t_map	*new_node;
	size_t	length;
	char	*update_line;

	length = ft_strlen(line);
	update_line = line;
	if (update_line[length - 1] != '\0')
	{
		update_line[length - 1] = '\0';
	}
	new_node = (t_map *)malloc(sizeof(t_map));
	if (!new_node)
		return (NULL);
	new_node->row_index = 0;
	new_node->row = update_line;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_to_end(t_map **head, char *line)
{
	t_map	*new_node;
	t_map	*temp;
	int		i;

	i = 1;
	new_node = create_node(line);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
			i++;
		}
		temp->next = new_node;
		temp->next->row_index = i;
		new_node->prev = temp;
	}
}

int	lstsize(t_map *stack)
{
	t_map	*current;
	int		i;

	current = stack;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}
////LINKED LIST MAP////////

#define WIDTH 1024
#define HEIGHT 512

// static void	error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

void	print_list(t_map *head)
{
	t_map	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s and index is: %d\n", temp->row, temp->row_index);
		temp = temp->next;
	}
	printf("\nNULL\n");
}

char	*join_str(char *buffer, char *tmp)
{
	char	*str;

	str = ft_strjoin(buffer, tmp);
	free(buffer);
	return (str);
}

void	initialize_map(void)
{
	int		fd;
	char	*line;
	char	*array;
	char	**map;
	int		i;
	
	fd = open("maps/map.ber", O_RDONLY);
	array = ft_strdup("");
	if (!array)
		return ;
	if (fd < 0)
	{
		printf("Error opening file");
		return ;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		array = join_str(array, line);
	}
	printf("STR LEN TEST: %zu\n", ft_strlen("324234"));
	close(fd);
	map = ft_split(array, '\n');
	if (map)
	{
		i = 0;
		while (map[i])
		{
			printf("result[%d] = %s\n", i, map[i]);
			i++;
		}
		i = 0;
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

int32_t	main(void)
{
	// mlx_t			*mlx;
	// mlx_texture_t	*texture;
	// mlx_texture_t	*asteroid;
	// mlx_image_t		*img;
	// mlx_image_t		*asteroid_img;
	initialize_map();
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
