/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_black.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:57:36 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/30 00:43:12 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_black(t_data *data, t_point p0, t_point p1)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = p1.x - p0.x;
	delta_y = p1.y - p0.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = p0.x;
	pixel_y = p0.y;
	while (pixels)
	{
		my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00000000);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

void	draw_horizontal_lines_black(t_point **coordinates, t_data img)
{
	int	l;
	int	c;

	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			draw_line_black(&img, coordinates[l][c],
				coordinates[l][c + 1]);
			c++;
		}
		c = 0;
		l++;
	}
}

void	draw_vertical_lines_black(t_point **coordinates, t_data img)
{
	int	l;
	int	c;

	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l + 1] && coordinates[l][c].next != NULL)
		{
			draw_line_black(&img, coordinates[l][c],
				coordinates[l + 1][c]);
			c++;
		}
		if (coordinates[l][c].next == NULL && coordinates[l + 1])
			draw_line_black(&img, coordinates[l][c],
				coordinates[l + 1][c]);
		l++;
		c = 0;
	}
}
