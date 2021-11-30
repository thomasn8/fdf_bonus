/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:20:47 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/29 15:21:26 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_z_min(t_point **coordinates)
{
	int	l;
	int	c;
	int	z_min;

	z_min = 0;
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			if (coordinates[l][c].z < z_min)
				z_min = coordinates[l][c].z;
			c++;
		}
		if (coordinates[l][c].z < z_min)
			z_min = coordinates[l][c].z;
		c = 0;
		l++;
	}
	return (z_min);
}

int	get_z_max(t_point **coordinates)
{
	int	l;
	int	c;
	int	z_max;

	z_max = 0;
	l = 0;
	c = 0;
	while (coordinates[l])
	{
		while (coordinates[l][c].next != NULL)
		{
			if (coordinates[l][c].z > z_max)
				z_max = coordinates[l][c].z;
			c++;
		}
		if (coordinates[l][c].z > z_max)
			z_max = coordinates[l][c].z;
		c = 0;
		l++;
	}
	return (z_max);
}
