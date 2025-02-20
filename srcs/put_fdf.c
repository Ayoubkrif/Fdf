/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 08:36:55 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/20 14:58:17 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

static t_projection	iv(int x, int y)
{
	t_projection	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	put_from_0_0(t_data *fdf)
{
	t_projection	current;
	int				x;
	int				y;

	x = 0;
	while (x < fdf->x_max)
	{
		y = 0;
		while (y < fdf->y_max)
		{
			current = project_iso(fdf->coordinate[y][x], x, y, fdf->option);
			if (x + 1 < fdf->x_max)
				line(fdf, current, iv(x, y), iv(x + 1, y));
			if (y + 1 < fdf->y_max)
				line(fdf, current, iv(x, y), iv(x, y + 1));
			if (x + 1 < fdf->x_max && y + 1 < fdf->y_max)
				line(fdf, current, iv(x, y), iv(x + 1, y + 1));
			if (x + 1 < fdf->x_max && y - 1 >= 0)
				line(fdf, current, iv(x, y), iv(x + 1, y - 1));
			if (x + 1 < fdf->x_max && y - 2 >= 0)
				line(fdf, current, iv(x, y), iv(x + 1, y - 2));
			if (x - 1 >= 0 && y - 2 >= 0)
				line(fdf, current, iv(x, y), iv(x - 1, y - 2));
			if (x + 2 < fdf->x_max && y - 1 >= 0)
				line(fdf, current, iv(x, y), iv(x + 2, y - 1));
			if (x - 2 >= 0 && y - 1 >= 0)
				line(fdf, current, iv(x, y), iv(x - 2, y - 1));
			y++;
		}
		x++;
	}
}

void	put_from_0_xmax(t_data *fdf)
{
	t_projection	current;
	int				x;
	int				y;

	x = fdf->x_max - 1;
	while (x >= 0)
	{
		y = 0;
		while (y < fdf->y_max)
		{
			current = project_iso(fdf->coordinate[y][x], x, y, fdf->option);
			if (x - 1 >= 0)
				line(fdf, current, iv(x, y), iv(x - 1, y));
			if (y + 1 < fdf->y_max)
				line(fdf, current, iv(x, y), iv(x, y + 1));
			y++;
		}
		x--;
	}
}

void	put_from_ymax_0(t_data *fdf)
{
	t_projection	current;
	int				x;
	int				y;

	x = 0;
	while (x < fdf->x_max)
	{
		y = fdf->y_max - 1;
		while (y >= 0)
		{
			current = project_iso(fdf->coordinate[y][x], x, y, fdf->option);
			if (x + 1 < fdf->x_max)
				line(fdf, current, iv(x, y), iv(x + 1, y));
			if (y - 1 >= 0)
				line(fdf, current, iv(x, y), iv(x, y - 1));
			y--;
		}
		x++;
	}
}

void	put_from_ymax_xmax(t_data *fdf)
{
	t_projection	current;
	int				x;
	int				y;

	x = fdf->x_max - 1;
	while (x >= 0)
	{
		y = fdf->y_max - 1;
		while (y >= 0)
		{
			current = project_iso(fdf->coordinate[y][x], x, y, fdf->option);
			if (x - 1 >= 0)
				line(fdf, current, iv(x, y), iv(x - 1, y));
			if (y - 1 >= 0)
				line(fdf, current, iv(x, y), iv(x, y - 1));
			y--;
		}
		x--;
	}
}
