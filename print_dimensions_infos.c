/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dimensions_infos.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:37:23 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/29 17:06:35 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	print_window_dimensions(t_vars vars, t_data img)
{
	int	win_w;
	int	win_h;

	win_w = vars.width - img.margin_width;
	win_h = vars.heigth - img.margin_heigth;
	ft_printf("WINDOW\n");
	ft_printf("- width : %d | heigth : %d\n", vars.width, vars.heigth);
	ft_printf("- margin left+right : %d | top+bot. : %d\n\n",
		img.margin_width, img.margin_heigth);
	ft_printf("IMAGE LIMITS\n");
	ft_printf("- width : %d | heigth : %d \n\n", win_w, win_h);
}

static void	print_cartesian_dimensions(char *maps, int points_spacing)
{
	int	cols;
	int	rows;
	int	img_w;
	int	img_h;

	cols = 0;
	rows = 0;
	get_cols_rows(maps, &cols, &rows);
	cols -= 1;
	rows -= 1;
	img_w = cols * points_spacing;
	img_h = rows * points_spacing;
	ft_printf("MAP (cartesian)\n");
	ft_printf("- width : %d (%d columns)\n", img_w, cols);
	ft_printf("- heigth : %d (%d rows)\n", img_h, rows);
	ft_printf("\n");
}

static void	print_ratios_dimensions(int points_spacing)
{
	ft_printf("RATIOS\n");
	ft_printf("- stroke length between points : %dpx\n", points_spacing);
	ft_printf("- z-ratio : %d/%d\n", points_spacing, Z_RATIO_DIVIDER);
	ft_printf("\n");
}

void	print_dimensions_info(
		char *maps, t_vars vars, t_data img, int points_spacing)
{
	ft_putstr_fd(YELLOW, 1);
	ft_printf("\n\n---------------------------\n");
	ft_putstr_fd(DEFAULT, 1);
	ft_printf("WINDOW AND MAP DIMENSIONS :\n");
	ft_putstr_fd(YELLOW, 1);
	ft_printf("---------------------------\n");
	print_window_dimensions(vars, img);
	print_cartesian_dimensions(maps, points_spacing);
	print_ratios_dimensions(points_spacing);
}
