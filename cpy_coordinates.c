/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:37:54 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/30 12:38:15 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	count_lines_cols(t_point **coordinates, int *line_n, int *col_n)
{
	int	l;
	int	c;

	l = 0;
	c = 0;
	while (coordinates[l])
	{
		*line_n += 1;
		l++;
	}
	l = 0;
	while (coordinates[l][c].next != NULL)
	{
		*col_n += 1;
		c++;
	}
}

static void	copy_points_coordinates(
	t_point **coordinates, t_point *line_coordinates, int l, int col_n)
{
	int	c;

	c = 0;
	while (c < col_n)
	{
		line_coordinates[c].x = coordinates[l][c].x;
		line_coordinates[c].y = coordinates[l][c].y;
		line_coordinates[c].z = coordinates[l][c].z;
		line_coordinates[c].next = coordinates[l][c].next;
		c++;
	}
	line_coordinates[c].x = coordinates[l][c].x;
	line_coordinates[c].y = coordinates[l][c].y;
	line_coordinates[c].z = coordinates[l][c].z;
	line_coordinates[c].next = coordinates[l][c].next;
}

t_point	**duplicate_coordinates(t_point **coordinates)
{
	t_point	**coordinates_cpy;
	int		line_n;
	int		col_n;
	t_point	*line_coordinates;
	int		l;

	coordinates_cpy = NULL;
	line_n = 0;
	col_n = 0;
	count_lines_cols(coordinates, &line_n, &col_n);
	coordinates_cpy = malloc((line_n + 1) * sizeof(t_point *));
	if (!coordinates_cpy)
		return (NULL);
	coordinates_cpy[line_n] = NULL;
	l = 0;
	while (l < line_n)
	{
		line_coordinates = malloc((col_n + 1) * sizeof(t_point));
		if (!line_coordinates)
			return (NULL);
		coordinates_cpy[l] = line_coordinates;
		copy_points_coordinates(coordinates, line_coordinates, l, col_n);
		l++;
	}
	return (coordinates_cpy);
}
