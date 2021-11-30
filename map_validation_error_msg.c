/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_error_msg.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:09:10 by tnanchen          #+#    #+#             */
/*   Updated: 2021/11/28 23:09:26 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line_count_error_msg(int n)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("\nMap error : each line must have ", 2);
	ft_putstr_fd("the same number of coordinate points\n", 2);
	ft_putstr_fd("Line n° ", 2);
	ft_putnbr_fd(n + 1, 2);
	ft_putstr_fd(" contains an invalid invalid number of ", 2);
	ft_putstr_fd("coordinate points compare to previous ones.\n", 2);
	exit (1);
}

void	line_count_zero_error_msg(int n)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("\nMap error : line ", 2);
	ft_putnbr_fd(n + 1, 2);
	ft_putstr_fd(" has no coordinates point\n", 2);
	exit (1);
}

void	value_error_msg(int n, int i)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("\nMap error : map values must be integers\n", 2);
	ft_putstr_fd("Line n° ", 2);
	ft_putnbr_fd(n + 1, 2);
	ft_putstr_fd(" contains an invalid character at position ", 2);
	ft_putnbr_fd(i + 1, 2);
	ft_putstr_fd(".\n", 2);
	exit (1);
}
