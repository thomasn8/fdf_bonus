/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 09:31:28 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/30 19:48:39 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_coordinates(t_point **coordinates)
{
	int	line;

	line = 0;
	while (coordinates[line])
	{
		free(coordinates[line]);
		line++;
	}
	free(coordinates);
}

static void	quit_prog(t_vars *vars)
{
	free_coordinates(vars->coordinates_origin);
	free_coordinates(vars->coordinates_cpy);
	printf("Origin coordinates are freed\n");
	printf("Quit program\n");
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	key_function(int key, t_vars *vars)
{
	if (key == ESC)
		quit_prog(vars);
	if (key == ARROW_DOWN || key == ARROW_UP)
		z_scale(key, vars);
	return (0);
}
