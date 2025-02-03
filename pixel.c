/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/03 12:44:36 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "lib.h"
#include <math.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

// Algorithme de Bresenham
void ft_draw_line_b(t_data *data, int x1, int y1, int x2, int y2, int color)
{
    int dx, dy, sx, sy, err, e2;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(data, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

//algo qui fonctionne
/*
void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
    int step;
    int x, y;
    int delta_x, delta_y;

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    step = fmax(fabs(delta_x), fabs(delta_y)); // Utilisation de `fmax` pour éviter des erreurs

    delta_x /= step;
    delta_y /= step;

    x = x1;
    y = y1;

    for (int i = 0; i <= step; i++)
    {
        my_mlx_pixel_put(data, round(x), round(y), color);
        x += delta_x;
        y += delta_y;
    }
}*/

t_projection	init_projection(int	x, int	y)
{
	t_projection	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	line(t_data img, t_projection current, t_projection next, int coulour)
{
	ft_draw_line_b(&img, current.x, current.y, next.x, next.y, coulour); //jaune
}


t_projection project_iso(int **z, int x, int y)
{
    t_projection	result;

    result.x = OFFSET + (STEP * (cos(ANGLE) * x - cos(ANGLE) * y));
    result.y = OFFSET + (STEP * (sin(ANGLE) * x + sin(ANGLE) * y - z[y][x]));
    return (result);
}

void	recurse(t_data img, t_projection current, int x, int y)
{
	t_projection	nextx;
	t_projection	nexty;

	if (x + 1 < img.x_max)
	{
		nextx = project_iso(img.coordinate, x + 1, y);
		line(img, current, nextx, 0x00FF0000); //jaune
		recurse(img, nextx, x + 1, y);
	}
	if (y + 1 < img.y_max)
	{
		nexty = project_iso(img.coordinate , x, y + 1);
		line(img, current, nexty, 0x0000FF00); //jaune
		recurse(img, nexty, x, y + 1);
	}
}

void	quadrillage(t_data img)
{
	recurse(img, img.start, 0, 0);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 65307) // Touche ESC pour quitter
		exit(0);
	if (keycode == 32) // Touche ESPACE pour lancer quadrillage
	{
		img->start = project_iso(img->coordinate, 0, 0);
		line(*img ,init_projection(0, 0), img->start,0x00FF0000);
		quadrillage(*img);
		mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	}
	return (0);
}
