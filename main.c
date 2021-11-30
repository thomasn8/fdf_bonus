/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:21:47 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/30 20:09:39 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	usage(void)
{
	ft_putstr_fd(YELLOW, 2);
	ft_putstr_fd("Usage: ./fdf \"map\"\n", 2);
	exit(1);
}

void	create_image(t_point **coordinates, t_vars vars, t_data img, char *maps)
{
	int	points_spacing;

	points_spacing = get_points_spacing(maps, vars, img);
	print_dimensions_info(maps, vars, img, points_spacing);
	isometric_transformations(coordinates, points_spacing, vars, img);
	check_limits_x(coordinates, vars, img);
	check_limits_y(coordinates, vars, img);
	draw_horizontal_lines(coordinates, img);
	draw_vertical_lines(coordinates, img);
}

int	main(int ac, char **av)
{
	t_point		**coordinates_origin;
	t_point		**coordinates_cpy;
	t_vars		vars;
	t_data		img;

	if (ac != 2)
		usage();
	coordinates_origin = create_coordinates(av[1]);
	coordinates_cpy = duplicate_coordinates(coordinates_origin);
	vars.mlx = mlx_init();
	vars.coordinates_origin = coordinates_origin;
	vars.coordinates_cpy = coordinates_cpy;
	vars.win = set_window(
			vars.mlx, &vars.width, &vars.heigth, "FDF - 42 project");
	img = set_image(vars);
	vars.image = &img;
	create_image(coordinates_cpy, vars, img, av[1]);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img,
		img.margin_width / 2, img.margin_heigth / 2);
	mlx_key_hook(vars.win, key_function, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

/*
BONUS :

- Ajouter un menu avec les commandes
- Ajouter d'autres type de projection
*/