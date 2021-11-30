/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_transformations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:25:01 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/30 19:49:34 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_points_spacing(char *maps, t_vars vars, t_data img)
{
	int	points_spacing;
	int	cols;
	int	rows;
	int	points_spacing_w;
	int	points_spacing_h;

	cols = 0;
	rows = 0;
	if (get_cols_rows(maps, &cols, &rows) < 0)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(
			"\nMap error : impossible to get total of columns and rows\n", 2);
		exit(1);
	}
	points_spacing_w = (vars.width - img.margin_width) * 3 / 4 / cols;
	points_spacing_h = (vars.heigth - img.margin_heigth) * 3 / 4 / rows;
	if (points_spacing_w > points_spacing_h)
		points_spacing = points_spacing_h;
	else
		points_spacing = points_spacing_w;
	get_points_spacing_2(points_spacing, 1);
	return (points_spacing);
}

int	get_points_spacing_2(int points_spacing, int call)
{
	static int	points_spacing_cpy = 0;

	if (call == 1)
		points_spacing_cpy = points_spacing;
	return (points_spacing_cpy);
}

void	iso(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

static void	isometric_transformations_2(
	t_point **coordinates, int points_spacing, int l, int *c)
{
	float	z_ratio;

	z_ratio = 0;
	z_ratio = points_spacing / Z_RATIO_DIVIDER;
	coordinates[l][*c].x *= points_spacing;
	coordinates[l][*c].y *= points_spacing;
	coordinates[l][*c].z *= (points_spacing / z_ratio);
	iso(&coordinates[l][*c].x, &coordinates[l][*c].y, coordinates[l][*c].z);
	*c += 1;
}

void	isometric_transformations(
	t_point **coordinates, int points_spacing, t_vars vars, t_data img)
{
	int			l;
	int			c;
	t_offset	offset;
	float		z_ratio;

	offset.y_max = 0;
	z_ratio = points_spacing / Z_RATIO_DIVIDER;
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
			isometric_transformations_2(coordinates, points_spacing, l, &c);
		coordinates[l][c].x *= points_spacing;
		coordinates[l][c].y *= points_spacing;
		coordinates[l][c].z *= (points_spacing / z_ratio);
		iso(&coordinates[l][c].x, &coordinates[l][c].y, coordinates[l][c].z);
		c = 0;
		l++;
	}
	center_y(offset, vars, img, coordinates);
	offset_x(offset, coordinates);
	center_x(offset, vars, img, coordinates);
	set_points_colors(coordinates);
}
