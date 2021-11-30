/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:18:37 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/29 16:06:09 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

static double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

static int	get_color(int current_z, int z_min, int z_max)
{
	t_color	rgb;
	double	percentage;
	int		z_min_color;
	int		z_max_color;

	z_min_color = Z_MIN_COLOR;
	z_max_color = Z_MAX_COLOR;
	percentage = percent(z_min, z_max, current_z);
	rgb.red = get_light(
			(z_min_color >> 16) & 0xFF, (z_max_color >> 16) & 0xFF, percentage);
	rgb.green = get_light(
			(z_min_color >> 8) & 0xFF, (z_max_color >> 8) & 0xFF, percentage);
	rgb.blue = get_light(
			z_min_color & 0xFF, z_max_color & 0xFF, percentage);
	return ((rgb.red << 16) | (rgb.green << 8) | rgb.blue);
}

void	set_points_colors(t_point **coordinates)
{
	int	z_min;
	int	z_max;
	int	l;
	int	c;

	z_min = get_z_min(coordinates);
	z_max = get_z_max(coordinates);
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			coordinates[l][c].color = get_color(
					coordinates[l][c].z, z_min, z_max);
			c++;
		}
		coordinates[l][c].color = get_color(coordinates[l][c].z, z_min, z_max);
		c = 0;
		l++;
	}
}
