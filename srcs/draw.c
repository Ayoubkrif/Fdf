/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:44:58 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/22 10:19:51 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINX && y >= 0 && y < WINY)
	{
		dst = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static int	is_in_window(t_projection pixel)
{
	if (pixel.x < 0 || pixel.x > WINX)
		return (0);
	if (pixel.y < 0 || pixel.y > WINY)
		return (0);
	return (1);
}

int	draw_line(t_data *fdf, t_projection start, t_projection end)
{
	t_projection	delta;
	t_projection	pixel;
	int				pixels;
	int				len;

	if (is_in_window(start) == 0 && is_in_window(end) == 0)
		return (0);
	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	pixels = sqrt((delta.x * delta.x) + \
			(delta.y * delta.y));
	len = pixels;
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = start.x;
	pixel.y = start.y;
	while (pixels > 0)
	{
		pixel.colour = interpolate_color(start.colour, end.colour, len, pixels);
		my_mlx_pixel_put(fdf, pixel.x, pixel.y, pixel.colour);
		pixel.x += delta.x;
		pixel.y += delta.y;
		pixels = pixels - 1;
	}
	return (1);
}

void	line(t_data *fdf, t_projection current, t_projection c, t_projection n)
{
	t_projection	next;

	next = project_iso(fdf->coordinate[(int)n.y][(int)n.x],
			n.x, n.y,
			fdf->option);
	current.colour = fdf->coordinate[(int)c.y][(int)c.x].colour;
	next.colour = fdf->coordinate[(int)n.y][(int)n.x].colour;
	draw_line(fdf, current, next);
}
