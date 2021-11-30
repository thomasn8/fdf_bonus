/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 01:44:19 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/28 13:19:25 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_y(
	t_offset offset, t_vars vars, t_data img, t_point **coordinates)
{
	int	win_h;
	int	img_h;
	int	vertical_offset;
	int	l;
	int	c;

	offset.y_max = get_y_max(coordinates);
	win_h = vars.heigth - img.margin_heigth;
	img_h = offset.y_max;
	vertical_offset = (win_h - img_h) / 2;
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			coordinates[l][c].y += vertical_offset;
			c++;
		}
		coordinates[l][c].y += vertical_offset;
		c = 0;
		l++;
	}
}

void	offset_x(t_offset offset, t_point **coordinates)
{
	int	l;
	int	c;

	offset.x_min = get_x_min(coordinates);
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			coordinates[l][c].x -= offset.x_min;
			c++;
		}
		coordinates[l][c].x -= offset.x_min;
		c = 0;
		l++;
	}
}

void	center_x(
	t_offset offset, t_vars vars, t_data img, t_point **coordinates)
{
	int	win_w;
	int	img_w;
	int	horizontal_offset;
	int	l;
	int	c;

	offset.x_max = get_x_max(coordinates);
	win_w = vars.width - img.margin_width;
	img_w = offset.x_max;
	horizontal_offset = (win_w - img_w) / 2;
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			coordinates[l][c].x += horizontal_offset;
			c++;
		}
		coordinates[l][c].x += horizontal_offset;
		c = 0;
		l++;
	}
}
