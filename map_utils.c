/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:29:19 by macbook           #+#    #+#             */
/*   Updated: 2024/11/18 02:08:27 by auplisas         ###   ########.fr       */
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

char	*join_str(char *buffer, char *tmp)
{
	char	*str;

	str = ft_strjoin(buffer, tmp);
	free(buffer);
	return (str);
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
