/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_limits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 21:50:27 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/30 20:30:08 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_limits_x(t_point **coordinates, t_vars vars, t_data img)
{
	int	win_w;
	int	x_min;
	int	x_max;
	int	img_width;

	win_w = vars.width - img.margin_width;
	x_min = get_x_min(coordinates);
	if (x_min < 0)
		x_min *= -1;
	x_max = get_x_max(coordinates);
	img_width = x_max + x_min;
	ft_printf("MAP (isometric)\n");
	ft_printf("- width : %d\n", img_width);
	if (img_width >= win_w)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("\nMap error : map is too large for the window\n", 2);
		exit(1);
	}
}

void	check_limits_y(t_point **coordinates, t_vars vars, t_data img)
{
	int	win_h;
	int	y_min;
	int	y_max;
	int	img_heigth;

	win_h = vars.heigth - img.margin_heigth;
	y_min = get_y_min(coordinates);
	if (y_min < 0)
		y_min *= -1;
	y_max = get_y_max(coordinates);
	img_heigth = y_max + y_min;
	ft_printf("- heigth : %d\n\n", img_heigth);
	ft_putstr_fd(GREEN, 1);
	if (img_heigth >= win_h)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("\nMap error : map is too heigh for the window\n", 2);
		exit(1);
	}
}

int	check_limits_y_scale(t_point **coordinates, t_vars vars, t_data img)
{
	int	win_h;
	int	y_min;
	int	y_max;
	int	img_heigth;

	win_h = vars.heigth - img.margin_heigth;
	y_min = get_y_min(coordinates);
	if (y_min < 0)
		y_min *= -1;
	y_max = get_y_max(coordinates);
	img_heigth = y_max + y_min;
	ft_putstr_fd(GREEN, 1);
	if (y_min > 0 || img_heigth >= win_h)
		return (0);
	return (1);
}
