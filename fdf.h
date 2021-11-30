/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:19:06 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/30 20:27:07 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// lib and functions
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

// to get screen dimensions
# include <CoreGraphics/CGDisplayConfiguration.h>

// defines
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define DEFAULT "\033[0m"
// # define Z_MIN_COLOR 0x0000FF00
// # define Z_MAX_COLOR 0x0000FF00
# define Z_MIN_COLOR 0x00009999
# define Z_MAX_COLOR 0x00FF5900
# define Z_RATIO_DIVIDER 1

# define ESC 53
# define ARROW_UP 126
# define ARROW_DOWN 125
# define SCROLL_UP 4
# define SCROLL_DOWN 5

// window
typedef struct s_vars {
	void			*mlx;
	void			*win;
	unsigned int	width;
	unsigned int	heigth;
	struct s_point	**coordinates_origin;
	struct s_point	**coordinates_cpy;
	struct s_data	*image;
}	t_vars;

// image displayed on window
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		margin_width;
	int		margin_heigth;
}	t_data;

// points coordinates
typedef struct s_point {
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_point	*next;
}	t_point;

// get extrem coordinates
typedef struct s_offset {
	int			y_max;
	int			x_min;
	int			x_max;
}	t_offset;

// get color
typedef struct s_color {
	int			red;
	int			green;
	int			blue;
}	t_color;

// scale infos
typedef struct s_scale_z {
	int			points_spacing;
	float		z_scale;
	float		z_ratio;
}	t_scale_z;

// create_coordinates.c
t_point	**create_coordinates(char *map);
int		count_line_elem(char **tab);

// cpy_coordinates.c
t_point	**duplicate_coordinates(t_point **coordinates);

// map_validation.c
int		map_validation(char *map);

// map_validation_error_msg.c
void	line_count_error_msg(int n);
void	line_count_zero_error_msg(int n);
void	value_error_msg(int n, int i);

// set_window_and_image.c
int		get_screen_resolution(unsigned int *width, unsigned int *height);
void	*set_window(void *mlx,
			unsigned int *width, unsigned int *heigth, char *title);
t_data	set_image(t_vars vars);

// print_dimensions_infos.c
void	print_dimensions_info(
			char *maps, t_vars vars, t_data img, int points_spacing);

// isometric_transformations.c
int		get_points_spacing(char *maps, t_vars vars, t_data img);
int		get_points_spacing_2(int points_spacing_cpy, int call);
void	iso(int *x, int *y, int z);
void	isometric_transformations(
			t_point **coordinates, int points_spacing, t_vars vars, t_data img);

// center_coordinates.c
void	center_y(t_offset offset,
			t_vars vars, t_data img, t_point **coordinates);
void	offset_x(t_offset offset, t_point **coordinates);
void	center_x(t_offset offset,
			t_vars vars, t_data img, t_point **coordinates);

// get_coordinates_1.c
int		get_cols_rows(char *map, int *cols, int *rows);
int		get_y_min(t_point **coordinates);
int		get_y_max(t_point **coordinates);
int		get_x_min(t_point **coordinates);
int		get_x_max(t_point **coordinates);

// color_points.c
void	set_points_colors(t_point **coordinates);

// get_coordinates_2.c
int		get_z_min(t_point **coordinates);
int		get_z_max(t_point **coordinates);

// check_limits.c
void	check_limits_x(t_point **coordinates, t_vars vars, t_data img);
void	check_limits_y(t_point **coordinates, t_vars vars, t_data img);
int		check_limits_y_scale(t_point **coordinates, t_vars vars, t_data img);

// draw.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_data *data, t_point p0, t_point p1);
void	draw_horizontal_lines(t_point **coordinates, t_data img);
void	draw_vertical_lines(t_point **coordinates, t_data img);

// color_lines.c
int		get_line_colors(
			int current_x, int current_y, t_point start, t_point end);

// my_events.c
void	free_coordinates(t_point **coordinates);
int		key_function(int key, t_vars *vars);
int		mouse_function(int button, int x, int y, t_vars *vars);

// scale_z.c
void	z_scale(int key, t_vars *vars);

// draw_black.c
void	draw_horizontal_lines_black(t_point **coordinates, t_data img);
void	draw_vertical_lines_black(t_point **coordinates, t_data img);

#endif
