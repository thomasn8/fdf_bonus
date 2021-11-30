/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:18:05 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/30 12:38:08 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	error(char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("\nFile error : impossible to ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int	count_line_elem(char **tab)
{
	int	n;

	n = -1;
	while (tab[++n])
		;
	return (n);
}

static void	get_points_coordinates(
	t_point *line_coordinates, int line_n, int line_col, char **line_splitted)
{
	int	col;

	col = 0;
	while (col < line_col)
	{
		if (col > 0)
			line_coordinates[col - 1].next = &line_coordinates[col];
		line_coordinates[col].x = col;
		line_coordinates[col].y = line_n - 1;
		line_coordinates[col].z = ft_atoi(line_splitted[col]);
		col++;
	}
	line_coordinates[col - 1].next = 0;
}

static int	parse_lines(int fd, t_point	**coordinates)
{
	char		*line;
	char		**line_splitted;
	int			line_n;
	int			line_col;
	t_point		*line_coordinates;

	line_n = 0;
	line_col = 0;
	while (1)
	{
		line = ft_strtrim(get_next_line(fd), " \n");
		if (!line)
			break ;
		line_splitted = ft_split(line, ' ');
		free(line);
		line_col = count_line_elem(line_splitted);
		line_coordinates = malloc((line_col + 1) * sizeof(t_point));
		if (!line_coordinates)
			return (-1);
		coordinates[line_n++] = line_coordinates;
		get_points_coordinates(line_coordinates,
			line_n, line_col, line_splitted);
		free(line_splitted);
	}
	return (0);
}

/*
Coordinates are stored like :
[ [{xyz}{xyz}{xyz}{xyz}] [{xyz}{xyz}{xyz}{xyz}] [{xyz}{xyz}{xyz}{xyz}] ]

where :
1. **coordinates			->	[ super-tab containing lines of coordinates ]
2. *line_coordinates		->	[tab containign coordinate points]
3. line_coordinates[col]	->	{3d coordinate points (int): xyz}

Exemple (flat map 3x3):
[
	[{0 0 0} {1 0 0} {2 0 0}]
	[{0 1 0} {1 1 0} {2 1 0}]
	[{0 2 0} {1 2 0} {2 2 0}]
]
*/
t_point	**create_coordinates(char *map)
{
	int		fd;
	int		line_n;
	t_point	**coordinates;

	fd = open(map, O_RDONLY);
	if (fd < 3)
		error("open the specified map file");
	line_n = map_validation(map);
	if (line_n < 0)
		error("read the file and/or to get valid coordinates from it");
	coordinates = malloc((line_n + 1) * sizeof(t_point *));
	if (!coordinates)
		return (NULL);
	coordinates[line_n] = NULL;
	if (parse_lines(fd, coordinates) < 0)
	{
		free_coordinates(coordinates);
		error("read the file and/or to get valid coordinates from it");
	}
	if (close(fd) < 0)
		return (NULL);
	return (coordinates);
}
