/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 08:36:55 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/22 10:07:08 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	start_fdf(t_data *fdf)
{
	int	render;

	render = fdf->render_from;
	fdf->option.offset = set_offset(*fdf);
	if (render == UP_LEFT)
		put_from_0_0(fdf);
	else if (render == UP_RIGHT)
		put_from_0_xmax(fdf);
	else if (render == DOWN_LEFT)
		put_from_ymax_0(fdf);
	else
		put_from_ymax_xmax(fdf);
}

void	put_from_0_0(t_data *fdf)
{
	int				x;
	int				y;
	t_projection	current;

	x = 0;
	while (x < fdf->x_max)
	{
		y = 0;
		while (y < fdf->y_max)
		{
			current = project_iso(fdf->coordinate[y][x], x, y, fdf->option);
			if (1)
				set_wired_frame1(fdf, current, x, y);
			if (1)
				set_wired_frame2(fdf, current, x, y);
			if (1)
				set_wired_frame3(fdf, current, x, y);
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
			if (1)
				set_wired_frame1(fdf, current, x, y);
			if (1)
				set_wired_frame2(fdf, current, x, y);
			if (1)
				set_wired_frame3(fdf, current, x, y);
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
			if (1)
				set_wired_frame1(fdf, current, x, y);
			if (1)
				set_wired_frame2(fdf, current, x, y);
			if (1)
				set_wired_frame3(fdf, current, x, y);
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
			if (1)
				set_wired_frame1(fdf, current, x, y);
			if (1)
				set_wired_frame2(fdf, current, x, y);
			if (1)
				set_wired_frame3(fdf, current, x, y);
			y--;
		}
		x--;
	}
}
