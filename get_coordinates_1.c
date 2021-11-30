/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:40:17 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/28 13:01:10 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_cols_rows(char *map, int *cols, int *rows)
{
	int		fd;
	char	*line;
	char	**line_splitted;
	int		line_col;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (-1);
	line_col = 0;
	line = map;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		*rows += 1;
		line_splitted = ft_split(line, ' ');
		line_col = count_line_elem(line_splitted);
		if (line_col > *cols)
			*cols = line_col;
	}
	if (close(fd) < 0)
		return (-1);
	return (0);
}

int	get_y_min(t_point **coordinates)
{
	int	l;
	int	c;
	int	y_min;

	y_min = 0;
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			if (coordinates[l][c].y < y_min)
				y_min = coordinates[l][c].y;
			c++;
		}
		if (coordinates[l][c].y < y_min)
			y_min = coordinates[l][c].y;
		c = 0;
		l++;
	}
	return (y_min);
}

int	get_y_max(t_point **coordinates)
{
	int	l;
	int	c;
	int	y_max;

	y_max = 0;
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			if (coordinates[l][c].y > y_max)
				y_max = coordinates[l][c].y;
			c++;
		}
		if (coordinates[l][c].y > y_max)
			y_max = coordinates[l][c].y;
		c = 0;
		l++;
	}
	return (y_max);
}

int	get_x_min(t_point **coordinates)
{
	int	l;
	int	c;
	int	x_min;

	x_min = 0;
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			if (coordinates[l][c].x < x_min)
				x_min = coordinates[l][c].x;
			c++;
		}
		if (coordinates[l][c].x < x_min)
			x_min = coordinates[l][c].x;
		c = 0;
		l++;
	}
	return (x_min);
}

int	get_x_max(t_point **coordinates)
{
	int	l;
	int	c;
	int	x_max;

	x_max = 0;
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			if (coordinates[l][c].x > x_max)
				x_max = coordinates[l][c].x;
			c++;
		}
		if (coordinates[l][c].x > x_max)
			x_max = coordinates[l][c].x;
		c = 0;
		l++;
	}
	return (x_max);
}
