/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:20:32 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/29 23:29:54 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_line_values(int n, char **l_split)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (l_split[++i])
	{
		if (l_split[i][j] == '+' || l_split[i][j] == '-')
			j++;
		while ((l_split[i][j] >= '0' && l_split[i][j] <= '9')
			|| (l_split[i][j] >= 'a' && l_split[i][j] <= 'f')
			|| l_split[i][j] == 'x' || l_split[i][j] == ',')
			j++;
		if (l_split[i][j] != 0 && (l_split[i][j] < '0' || l_split[i][j] > '9'))
			value_error_msg(n, i);
		j = 0;
	}
}

static void	check_line_count_and_values(int n, char *line)
{
	static int	line_count = 0;
	char		**line_splitted;

	line_splitted = ft_split(line, ' ');
	if (line_count == 0)
		line_count = count_line_elem(line_splitted);
	else
	{
		if (line_count != count_line_elem(line_splitted))
			line_count_error_msg(n);
	}
	if (!line_count)
		line_count_zero_error_msg(n);
	check_line_values(n, line_splitted);
	free(line_splitted);
	free(line);
}

int	map_validation(char *map)
{
	int		fd;
	char	*line;
	int		n;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (-1);
	n = 0;
	while (1)
	{
		line = ft_strtrim(get_next_line(fd), " \n");
		if (!n && !line)
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd("\nMap error : empty file\n", 2);
			exit (1);
		}
		if (!line)
			break ;
		check_line_count_and_values(n, line);
		n++;
	}
	if (close(fd) < 0)
		return (-1);
	return (n);
}
