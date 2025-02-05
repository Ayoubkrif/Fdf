/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/05 08:46:24 by aykrifa          ###   ########.fr       */
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

int interpolate_color(int color1, int color2, float t)
{
    int r1 = (color1 >> 16) & 0xFF; // Rouge du point 1
    int g1 = (color1 >> 8)  & 0xFF; // Vert du point 1
    int b1 =  color1        & 0xFF; // Bleu du point 1

    int r2 = (color2 >> 16) & 0xFF; // Rouge du point 2
    int g2 = (color2 >> 8)  & 0xFF; // Vert du point 2
    int b2 =  color2        & 0xFF; // Bleu du point 2

    // 🔹 Interpolation linéaire pour chaque canal
    int r = (int)(r1 + t * (r2 - r1));
    int g = (int)(g1 + t * (g2 - g1));
    int b = (int)(b1 + t * (b2 - b1));

    // 🔹 Reconstruction de la couleur (format 0xRRGGBB)
    return ((r << 16) | (g << 8) | b);
}// Algorithme de Bresenham

void ft_draw_line_b(t_data *data, int x1, int y1, int x2, int y2, int color1, int color2)
{
    int dx, dy, sx, sy, err, e2;
    int	length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2- y1));
    int	step = 0;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;

    while (1)
    {
	float t = (length == 0) ? 0 : (float)step / length;
	int color = interpolate_color(color1, color2, t);
        my_mlx_pixel_put(data, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
	step++;
    }
    my_mlx_pixel_put(data, x1, y1, color1);
    my_mlx_pixel_put(data, x2, y2, color2);
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

void	line(t_data img, t_projection current, t_projection next, int xc, int yc, int xn, int yn)
{
	ft_draw_line_b(&img, current.x, current.y, next.x, next.y, img.coordinate[yc][xc].colour, img.coordinate[yn][xn].colour); //jaune
}


t_projection project_iso(t_coordinate **point, int x, int y)
{
    t_projection	result;

    result.x = 1000 + OFFSET + (STEP * (cos(ANGLE) * x - cos(ANGLE) * y));
    result.y = OFFSET + (STEP * (sin(ANGLE) * x + sin(ANGLE) * y - point[y][x].z));
	result.colour = point[y][x].colour;
    return (result);
}

/*void	recurse(t_data img, t_projection current, int x, int y)
{
	t_projection	nextx;
	t_projection	nexty;

	if (x + 1 < img.x_max)
	{
		nextx = project_iso(img.coordinate, x + 1, y);
		line(img, current, nextx, x, y, x + 1, y); //jaune
		recurse(img, nextx, x + 1, y);
	}
	if (y + 1 < img.y_max)
	{
		nexty = project_iso(img.coordinate , x, y + 1);
		line(img, current, nexty, x, y, x, y + 1); //jaune
		recurse(img, nexty, x, y + 1);
	}
}*/

void	recurse(t_data img)
{
	t_projection	next;
	t_projection	current;
	int				x;
	int				y;

	x = 0;
	while (x < img.x_max)
	{
		y = 0;
		while (y < img.y_max)
		{
			current = project_iso(img.coordinate, x, y);
			if (x + 1 < img.x_max)
			{
				next = project_iso(img.coordinate, x + 1, y);
				line(img, current, next, x, y, x + 1, y); //jaune
			}
			if (y + 1 < img.y_max)
			{
				next = project_iso(img.coordinate , x, y + 1);
				line(img, current, next, x, y, x, y + 1); //jaune
			}
			y++;
		}
		x++;
	}
}

void	quadrillage(t_data img)
{
	recurse(img);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 65307) // Touche ESC pour quitter
		exit(0);
	if (keycode == 32) // Touche ESPACE pour lancer quadrillage
	{
		ft_draw_line_b(img, 0, 0, project_iso(img->coordinate, 0, 0).x, project_iso(img->coordinate, 0, 0).y, 0xFFFFFF, img->coordinate[0][0].colour); //jaune
		quadrillage(*img);
		mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	}
	return (0);
}
