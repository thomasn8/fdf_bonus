/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_window_and_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:39:02 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/28 21:59:38 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_screen_resolution(unsigned int *width, unsigned int *height)
{
	CGDirectDisplayID	main_display_id;

	main_display_id = CGMainDisplayID();
	*width = CGDisplayPixelsWide(main_display_id);
	*height = CGDisplayPixelsHigh(main_display_id);
	if (*width > 0 && *height > 0)
		return (0);
	return (-1);
}

void	*set_window(void *mlx,
			unsigned int *width, unsigned int *heigth, char *title)
{
	unsigned int	margin_w;
	unsigned int	margin_h;
	void			*win;

	margin_w = 0;
	margin_h = 80;
	if (get_screen_resolution(width, heigth) < 0)
	{
		*width = 800;
		*heigth = 600;
		win = mlx_new_window(mlx, 800, 600, title);
	}
	else
	{
		*width = *width - margin_w;
		*heigth = *heigth - margin_h;
		win = mlx_new_window(mlx, *width, *heigth, title);
	}
	return (win);
}

t_data	set_image(t_vars vars)
{
	t_data	img;
	int		margin_width;
	int		margin_heigth;

	margin_width = vars.width / 6;
	margin_heigth = vars.heigth / 8;
	img.img = mlx_new_image(
			vars.mlx, vars.width - margin_width, vars.heigth - margin_heigth);
	img.addr = mlx_get_data_addr(
			img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.margin_width = margin_width;
	img.margin_heigth = margin_heigth;
	return (img);
}
