/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 08:36:55 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/16 14:24:49 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

static t_projection	iv(int x, int y)
{
	t_projection point;
	point.x = x;
	point.y = y;
	return (point);
}

void	put_new_img(t_data *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->addr = mlx_get_data_addr(fdf->img,
			&fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	start_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void	line(t_data fdf, t_projection current, int xc, int yc, int xn, int yn)
{
	t_projection	next;

	next = project_iso(fdf.coordinate[yn][xn], xn, yn, fdf.option);
	ft_draw_line_b(&fdf, current.x, current.y, next.x, next.y,
		fdf.coordinate[yc][xc].colour,
		fdf.coordinate[yn][xn].colour);
}

void	start_fdf(t_data *fdf)
{
	int	render;

	render = fdf->render_from;
	fdf->option.offset = set_offset(*fdf);
	printf("x : %f, y : %f, z : %f\n",360 * fdf->angle.x / (PI * 2),360 * fdf->angle.y / (PI * 2),360 * fdf->angle.z / (PI * 2));
	if (render == UP_LEFT)
		put_from_0_0(*fdf);
	else if (render == UP_RIGHT)
		put_from_0_xmax(*fdf);
	else if (render == DOWN_LEFT)
		put_from_ymax_0(*fdf);
	else
		put_from_ymax_xmax(*fdf);
}

void	put_from_0_0(t_data fdf)
{
	t_projection	current;
	int				x;
	int				y;

	x = 0;
	while (x < fdf.x_max)
	{
		y = 0;
		while (y < fdf.y_max)
		{
			current = project_iso(fdf.coordinate[y][x], x, y, fdf.option);
			if (x + 1 < fdf.x_max)
				line(fdf, current, x, y, x + 1, y);
			if (y + 1 < fdf.y_max)
				line(fdf, current, x, y, x, y + 1);
			if (x + 1 < fdf.x_max && y + 1 < fdf.y_max)
				line(fdf, current, x, y, x + 1, y + 1);
			if (x + 1 < fdf.x_max && y - 1 >= 0)
				line(fdf, current, x, y, x + 1, y - 1);
			y++;
		}
		x++;
	}
}

void	put_from_0_xmax(t_data fdf)
{
	t_projection	current;
	int				x;
	int				y;

	x = fdf.x_max - 1;
	while (x >= 0)
	{
		y = 0;
		while (y < fdf.y_max)
		{
			current = project_iso(fdf.coordinate[y][x], x, y, fdf.option);
			if (x - 1 >= 0)
				line(fdf, current, x, y, x - 1, y);
			if (y + 1 < fdf.y_max)
				line(fdf, current, x, y, x, y + 1);
			y++;
		}
		x--;
	}
}

void	put_from_ymax_0(t_data fdf)
{
	t_projection	current;
	int				x;
	int				y;

	x = 0;
	while (x < fdf.x_max)
	{
		y = fdf.y_max - 1;
		while (y >= 0)
		{
			current = project_iso(fdf.coordinate[y][x], x, y, fdf.option);
			if (x + 1 < fdf.x_max)
				line(fdf, current, x, y, x + 1, y);
			if (y - 1 >= 0)
				line(fdf, current, x, y, x, y - 1);
			y--;
		}
		x++;
	}
}

void	put_from_ymax_xmax(t_data fdf)
{
	t_projection	current;
	int				x;
	int				y;

	x = fdf.x_max - 1;
	while (x >= 0)
	{
		y = fdf.y_max - 1;
		while (y >= 0)
		{
			current = project_iso(fdf.coordinate[y][x], x, y, fdf.option);
			if (x - 1 >= 0)
				line(fdf, current, x, y, x - 1, y);
			if (y - 1 >= 0)
				line(fdf, current, x, y, x, y - 1);
			y--;
		}
		x--;
	}
}
