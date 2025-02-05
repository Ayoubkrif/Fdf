/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/05 22:34:53 by aykrifa          ###   ########.fr       */
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

int	interpolate_color(int color1, int color2, float t)
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

t_projection project_iso_bonus(t_data fdf, int x, int y)
{
    t_projection result;
    double x_rot, y_rot, z_rot;
    double x_temp, y_temp, z_temp;
    
    // Récupération des coordonnées initiales
    double x0 = x;
    double y0 = y;
    double z0 = fdf.coordinate[y][x].z;

    // Rotation autour de l'axe X (pitch)
    y_temp = cos(fdf.angle.x) * y0 - sin(fdf.angle.x) * z0;
    z_temp = sin(fdf.angle.x) * y0 + cos(fdf.angle.x) * z0;
    y_rot = y_temp;
    z_rot = z_temp;

    // Rotation autour de l'axe Y (yaw)
    x_temp = cos(fdf.angle.y) * x0 + sin(fdf.angle.y) * z_rot;
    z_temp = -sin(fdf.angle.y) * x0 + cos(fdf.angle.y) * z_rot;
    x_rot = x_temp;
    z_rot = z_temp;

    // Rotation autour de l'axe Z (roll)
    x_temp = cos(fdf.angle.z) * x_rot - sin(fdf.angle.z) * y_rot;
    y_temp = sin(fdf.angle.z) * x_rot + cos(fdf.angle.z) * y_rot;
    x_rot = x_temp;
    y_rot = y_temp;

    // Projection isométrique
    result.x = fdf.offset.x + (STEP * (x_rot - y_rot));
    result.y = fdf.offset.y + (STEP * (x_rot + y_rot) / 2 - z_rot);
    result.colour = fdf.coordinate[y][x].colour;

    return (result);
}

int	distance(int a, int b)
{
	return ((a + b) / 2);
}

t_projection	project_3d_to_2d(int x, int y, int z, t_data img)
{
    t_projection result;
    double x_rot, y_rot, z_rot;
    double x_temp, y_temp, z_temp;

    // Rotation autour de X (Pitch)
    y_temp = cos(img.angle.x) * y - sin(img.angle.x) * z;
    z_temp = sin(img.angle.x) * y + cos(img.angle.x) * z;
    y_rot = y_temp;
    z_rot = z_temp;

    // Rotation autour de Y (Yaw)
    x_temp = cos(img.angle.y) * x + sin(img.angle.x) * z_rot;
    z_temp = -sin(img.angle.y) * x + cos(img.angle.x) * z_rot;
    x_rot = x_temp;
    z_rot = z_temp;

    // Rotation autour de Z (Roll)
    x_temp = cos(img.angle.z) * x_rot - sin(img.angle.z) * y_rot;
    y_temp = sin(img.angle.z) * x_rot + cos(img.angle.z) * y_rot;
    x_rot = x_temp;
    y_rot = y_temp;

    // Projection 2D
    result.x = x_rot;
    result.y = y_rot;

    return result;
}
t_offset	set_offset(t_data img)
{
	t_offset		offset;
	t_projection	middle;

	middle = project_3d_to_2d(img.x_max / 2, img.y_max / 2, distance(img.z_max, img.z_min), img);
	offset.x = 960 - middle.x;
	offset.y = 540 - middle.y;
	return (offset);
}

void	recurse(t_data fdf)
{
	t_projection	next;
	t_projection	current;
	int				x;
	int				y;

	x = 0;
	fdf.offset = set_offset(fdf);
	while (x < fdf.x_max)
	{
		y = 0;
		while (y < fdf.y_max)
		{
			current = project_iso_bonus(fdf, x, y);
			if (x + 1 < fdf.x_max)
			{
				next = project_iso_bonus(fdf, x + 1, y);
				line(fdf, current, next, x, y, x + 1, y); //jaune
			}
			if (y + 1 < fdf.y_max)
			{
				next = project_iso_bonus(fdf, x, y + 1);
				line(fdf, current, next, x, y, x, y + 1); //jaune
			}
			y++;
		}
		x++;
	}
}

void	put_new_img(t_data *img)
{
	mlx_clear_window(img->mlx, img->win); // Efface l'ancienne image
	mlx_destroy_image(img->mlx, img->img); // Supprime l'image précédente
	img->img = mlx_new_image(img->mlx, 1920, 1080); // Crée une nouvelle image
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	recurse(*img); // Redessine la grille
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == KEY_Q)
	{
		img->angle.x += PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_A)
	{
		img->angle.x -= PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_W)
	{
		img->angle.y += PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_S)
	{
		img->angle.y -= PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_E)
	{
		img->angle.z += PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_D)
	{
		img->angle.z -= PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_ESC) // Touche ESC pour quitter
		exit(0);
	if (keycode == KEY_SPACE) // Touche ESPACE pour lancer quadrillage
	{
		recurse(*img);
		mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	}
	return (0);
}

/*
t_projection project_spherical(t_data fdf, int x, int y)
{
    t_projection result;
    double r, theta, phi;
    double x_rot, y_rot, z_rot;

    // Coordonnées initiales
    double x0 = x;
    double y0 = y;
    double z0 = fdf.coordinate[y][x].z;

    // Appliquer la rotation en 3D
    double x_temp, y_temp, z_temp;

    // Rotation autour de X (pitch)
    y_temp = cos(fdf.angle.x) * y0 - sin(fdf.angle.x) * z0;
    z_temp = sin(fdf.angle.x) * y0 + cos(fdf.angle.x) * z0;
    y_rot = y_temp;
    z_rot = z_temp;

    // Rotation autour de Y (yaw)
    x_temp = cos(fdf.angle.y) * x0 + sin(fdf.angle.y) * z_rot;
    z_temp = -sin(fdf.angle.y) * x0 + cos(fdf.angle.y) * z_rot;
    x_rot = x_temp;
    z_rot = z_temp;

    // Rotation autour de Z (roll)
    x_temp = cos(fdf.angle.z) * x_rot - sin(fdf.angle.z) * y_rot;
    y_temp = sin(fdf.angle.z) * x_rot + cos(fdf.angle.z) * y_rot;
    x_rot = x_temp;
    y_rot = y_temp;

    // Conversion en coordonnées sphériques
    r = sqrt(x_rot * x_rot + y_rot * y_rot + z_rot * z_rot);
    theta = atan2(y_rot, x_rot); // fdf.angle azimutal
    phi = acos(z_rot / r);       // Angle d'élévation

    // Projection sphérique en 2D
    result.x = fdf.offset.x + (STEP * r * sin(phi) * cos(theta));
    result.y = fdf.offset.y + (STEP * r * sin(phi) * sin(theta));
    result.colour = fdf.coordinate[y][x].colour;

    return result;
}*/

/*
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
*/

/*
t_projection project_iso(t_coordinate **point, int x, int y)
{
    t_projection	result;

    result.x = 1000 + OFFSET + (STEP * (cos(ANGLE) * x - cos(ANGLE) * y));
    result.y = OFFSET + (STEP * (sin(ANGLE) * x + sin(ANGLE) * y - point[y][x].z));
	result.colour = point[y][x].colour;
    return (result);
}*/

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
