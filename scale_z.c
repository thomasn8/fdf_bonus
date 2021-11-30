/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_z.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 23:45:51 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/30 20:02:18 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	scaling_end(
	t_point **coordinates, t_scale_z scale, int l, int *c)
{
	coordinates[l][*c].x *= scale.points_spacing;
	coordinates[l][*c].y *= scale.points_spacing;
	coordinates[l][*c].z *= (scale.points_spacing / scale.z_ratio);
	iso(&coordinates[l][*c].x, &coordinates[l][*c].y, coordinates[l][*c].z);
	*c += 1;
}

static void	scaling(
	t_point **coordinates, float z_scale, t_vars vars, t_data img)
{
	int			l;
	int			c;
	t_offset	offset;
	t_scale_z	scale;

	scale.points_spacing = get_points_spacing_2(0, 2);
	scale.z_scale = z_scale;
	offset.y_max = 0;
	scale.z_ratio = scale.points_spacing / (Z_RATIO_DIVIDER + z_scale);
	l = -1;
	c = 0;
	while (coordinates[++l])
	{
		while (coordinates[l][c].next != NULL)
			scaling_end(coordinates, scale, l, &c);
		coordinates[l][c].x *= scale.points_spacing;
		coordinates[l][c].y *= scale.points_spacing;
		coordinates[l][c].z *= (scale.points_spacing / scale.z_ratio);
		iso(&coordinates[l][c].x, &coordinates[l][c].y, coordinates[l][c].z);
		c = 0;
	}
	center_y(offset, vars, img, coordinates);
	offset_x(offset, coordinates);
	center_x(offset, vars, img, coordinates);
	set_points_colors(coordinates);
}

static t_point	**new_coordinates(t_vars *vars, float z_scale)
{
	t_point	**coordinates_cpy;

	free_coordinates(vars->coordinates_cpy);
	coordinates_cpy = duplicate_coordinates(vars->coordinates_origin);
	vars->coordinates_cpy = coordinates_cpy;
	scaling(vars->coordinates_cpy, z_scale, *vars, *vars->image);
	return (coordinates_cpy);
}

void	z_scale(int key, t_vars *vars)
{
	static float	z_scale = 0;
	t_point			**coordinates_cpy;

	if (key == ARROW_UP)
		z_scale += 0.5;
	else
		z_scale -= 0.5;
	draw_horizontal_lines_black(vars->coordinates_cpy, *vars->image);
	draw_vertical_lines_black(vars->coordinates_cpy, *vars->image);
	coordinates_cpy = new_coordinates(vars, z_scale);
	if (!check_limits_y_scale(vars->coordinates_cpy, *vars, *vars->image))
	{
		if (key == ARROW_UP)
			z_scale -= 0.5;
		else
			z_scale += 0.5;
		coordinates_cpy = new_coordinates(vars, z_scale);
	}
	draw_horizontal_lines(vars->coordinates_cpy, *vars->image);
	draw_vertical_lines(vars->coordinates_cpy, *vars->image);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image->img,
		vars->image->margin_width / 2, vars->image->margin_heigth / 2);
}
