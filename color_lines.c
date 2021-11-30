/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:49:11 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/29 16:59:19 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	calc_delta(t_point delta, t_point p0, t_point p1)
{
	double	delta_x;
	double	delta_y;
	int		pixels;

	delta_x = p1.x - p0.x;
	delta_y = p1.y - p0.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta.x = delta_x / pixels;
	delta.y = delta_y / pixels;
	return (delta);
}

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

int	get_line_colors(int current_x, int current_y, t_point start, t_point end)
{
	t_point	delta;
	t_color	rgb;
	double	percentage;

	delta.color = 0;
	delta = calc_delta(delta, start, end);
	if (delta.x > delta.y)
		percentage = percent(start.x, end.x, current_x);
	else
		percentage = percent(start.y, end.y, current_y);
	rgb.red = get_light(
			(start.color >> 16) & 0xFF, (end.color >> 16) & 0xFF, percentage);
	rgb.green = get_light(
			(start.color >> 8) & 0xFF, (end.color >> 8) & 0xFF, percentage);
	rgb.blue = get_light(start.color & 0xFF, end.color & 0xFF, percentage);
	return ((rgb.red << 16) | (rgb.green << 8) | rgb.blue);
}
