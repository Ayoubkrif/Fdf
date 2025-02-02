/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/02 11:54:40 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "lib.h"
#include <math.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
    int step;
    double x, y;
    double delta_x, delta_y;

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
}

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

void	recurse(t_data img, t_projection current, t_projection end)
{
	int dist = 30;
	t_projection	nextx = init_projection(current.x + dist, current.y);
	t_projection	nexty = init_projection(current.x , current.y + dist);

	if (nextx.x <= end.x)
	{
		line(img, current, nextx, 0x00FF0000); //jaune
		recurse(img, nextx, end);
	}
	if (nexty.y <= end.y)
	{
		line(img, current, nexty, 0x0000FF00); //jaune
		recurse(img, nexty, end);
	}
}

void	quadrillage(t_data img, t_projection start, int n_x, int n_y)
{
	t_projection	end = init_projection(n_x * 20, n_y * 20);

	recurse(img, start, end);
}

int	key_hook(int keycode, t_data *img)
{
	static int x = 3;
	static int y = 3;
	static int startx = 10;
	static int starty = 10;


	if (keycode == 65307) // Touche ESC pour quitter
		exit(0);
	if (keycode == 65363) // droite
		startx++;
	if (keycode == 65361) // gauche
		startx--;
	if (keycode == 65364) // bas
		starty++;
	if (keycode == 65362) // haut
		starty--;
	if (keycode == 97) // a
		x++;
	if (keycode == 122) // z
		x--;
	if (keycode == 113) // q
		y++;
	if (keycode == 119) // w
		y--;
	if (keycode == 32) // Touche ESPACE pour lancer quadrillage
	{
		t_projection start = init_projection(startx, starty);
		quadrillage(*img, start, x, y);
		mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	}
	return (0);
}
