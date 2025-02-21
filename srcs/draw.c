/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:44:58 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/21 12:54:39 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
		dst = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	gradient(int startcolor, int endcolor, int len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((endcolor >> 16) - \
					(startcolor >> 16)) / (double)len;
	increment[1] = (double)(((endcolor >> 8) & 0xFF) - \
					((startcolor >> 8) & 0xFF)) / (double)len;
	increment[2] = (double)((endcolor & 0xFF) - (startcolor & 0xFF)) \
					/ (double)len;
	new[0] = (startcolor >> 16) + ft_round(pix * increment[0]);
	new[1] = ((startcolor >> 8) & 0xFF) + ft_round(pix * increment[1]);
	new[2] = (startcolor & 0xFF) + ft_round(pix * increment[2]);
	newcolor = (new[0] << 16) + (new[1] << 8) + new[2];
	return (newcolor);
}

int	valid_pixel(t_projection pixel)
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

	if (valid_pixel(start) == 0 && valid_pixel(end) == 0)
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
		pixel.colour = interpolate_color(start.colour, end.colour, (float)len, (float)pixels);
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
