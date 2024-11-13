/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:44:36 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/13 04:13:29 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// typedef struct t_map
// {
// 	void *mlx_ptr;     // MLX pointer
// 	void *win_ptr;     // MLX window pointer
// 	void *textures[5]; // MLX image pointers (on the stack)
// 	t_map *map;        // Map pointer (contains map details- preferably kept on the stack)
// }						t_data;

typedef struct s_stack_map
{
	int					row_index;
	char				*row;
	struct s_stack_map	*next;
	struct s_stack_map	*prev;
}						t_map;

# include "./MLX42/include/MLX42/MLX42.h"
# include "lib/lib.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

#endif