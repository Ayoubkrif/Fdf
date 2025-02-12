/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/12 09:15:22 by aykrifa          ###   ########.fr       */
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

int	interpolate_color(int color1, int color2, float t)
{
	int	red;
	int	green;
	int	blue;

	blue = (color1 % 256) * (1 - t) + (color2 % 256) * t;
	color1 /= 256;
	color2 /= 256;
	green = (color1 % 256) * (1 - t) + (color2 % 256) * t;
	green *= 256;
	color1 /= 256;
	color2 /= 256;
	red = (color1 % 256) * (1 - t) + (color2 % 256) * t;
	red *= 256 * 256;
	return (red + green + blue);
}

t_projection	init_projection(int x, int y)
{
	t_projection	point;

	point.x = x;
	point.y = y;
	return (point);
}

void ft_draw_line_b(t_data *data, int x1, int y1, int x2, int y2, int color1, int color2)
{
	float	length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2- y1));
	int		step = 0;
	int 	color;
	float	t;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = -1;
	if (x1 < x2)
		sx = 1;
	int sy = -1;
	if (y1 < y2)
		sy = 1;
	int err = dx - dy;
	while (TRUE)
	{
		t = 0 ;
		if (length != 0)
			t = step / length;
		color = color1;
		if (color1 != color2)
			color = interpolate_color(color1, color2, t);
		my_mlx_pixel_put(data, x1, y1, color);
		if ((x1 == x2 && y1 == y2) || x1 >= 1920 || y1 >= 1079)
			break ;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
		step++;
	}
	my_mlx_pixel_put(data, x1, y1, color1);
	my_mlx_pixel_put(data, x2, y2, color2);
}

void	line(t_data img, t_projection current, t_projection next, int xc, int yc, int xn, int yn)
{
	ft_draw_line_b(&img, current.x, current.y, next.x, next.y, img.coordinate[yc][xc].colour, img.coordinate[yn][xn].colour); //jaune
}

t_projection	project_iso(t_coordinate point, int x, int y, t_option opt)
{
	t_projection	result;
	t_vect			rot;
	float			tmp;

	rot.y = opt.angle.cos_x * y - opt.angle.sin_x * point.z;
	rot.z = opt.angle.sin_x * y + opt.angle.cos_x * point.z;
	rot.x = opt.angle.cos_y * x + opt.angle.sin_y * rot.z;
	rot.z = -opt.angle.sin_y * x + opt.angle.cos_y * rot.z;
	tmp = rot.x;
	rot.x = opt.angle.cos_z * rot.x - opt.angle.sin_z * rot.y;
	rot.y = opt.angle.sin_z * tmp + opt.angle.cos_z * rot.y;
	result.x = opt.translate.x + opt.offset.x + (opt.zoom * rot.x);
	result.y = opt.translate.y + opt.offset.y + (opt.zoom * rot.y);
	result.colour = point.colour;
	return (result);
}

float	distance(int a, int b)
{
	return ((a + b) / 2);
}

t_projection	project_3d_to_2d(int x, int y, int z, t_option opt)
{
	t_projection	result;
	t_vect			rot;
	float			tmp;

	rot.y = opt.angle.cos_x * y - opt.angle.sin_x * z;
	rot.z = opt.angle.sin_x * y + opt.angle.cos_x * z;
	rot.x = opt.angle.cos_y * x + opt.angle.sin_y * rot.z;
	rot.z = -opt.angle.sin_y * x + opt.angle.cos_y * rot.z;
	tmp = rot.x;
	rot.x = opt.angle.cos_z * rot.x - opt.angle.sin_z * rot.y;
	rot.y = opt.angle.sin_z * tmp + opt.angle.cos_z * rot.y;
	result.x = (opt.zoom * rot.x);
	result.y = (opt.zoom * rot.y);
	return (result);
}

t_offset	set_offset(t_data img)
{
	t_offset		offset;
	t_projection	middle;

	middle = project_3d_to_2d(img.x_max / 2, img.y_max / 2, distance(img.z_max, img.z_min), img.option);
	offset.x = 960 - middle.x;
	offset.y = 540 - middle.y;
	ft_draw_line_b(&img, 0, 0, middle.x + offset.x, middle.y + offset.y, 0x0, 0xFFFFFF);
	return (offset);
}

void	recurse(t_data fdf)
{
	t_projection	next;
	t_projection	current;
	int				x;
	int				y;

	x = 0;
	fdf.option.offset = set_offset(fdf);
	while (x < fdf.x_max)
	{
		y = 0;
		while (y < fdf.y_max)
		{
			current = project_iso(fdf.coordinate[y][x], x, y, fdf.option);
			if (x + 1 < fdf.x_max)
			{
				next = project_iso(fdf.coordinate[y][x + 1], x + 1, y, fdf.option);
				line(fdf, current, next, x, y, x + 1, y); //jaune
			}
			if (y + 1 < fdf.y_max)
			{
				next = project_iso(fdf.coordinate[y + 1][x], x, y + 1, fdf.option);
				line(fdf, current, next, x, y, x, y + 1); //jaune
			}
			y++;
		}
		x++;
	}
}

/*
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
    x_temp = cos(img.angle.y) * x + sin(img.angle.y) * z_rot;
    z_temp = -sin(img.angle.y) * x + cos(img.angle.y) * z_rot;
    x_rot = x_temp;
    z_rot = z_temp;

    // Rotation autour de Z (Roll)
    x_temp = cos(img.angle.z) * x_rot - sin(img.angle.z) * y_rot;
    y_temp = sin(img.angle.z) * x_rot + cos(img.angle.z) * y_rot;
    x_rot = x_temp;
    y_rot = y_temp;

    // Projection 2D
    result.x = (x_rot - y_rot) * STEP;
    result.y = (STEP * ((((x_rot + y_rot) / 2) - z_rot)));

    return result;
}
struct of array > array of struct
*/

/*t_projection project_iso_bonus(t_data fdf, int x, int y)
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
    result.y = fdf.offset.y + (STEP * ((((x_rot + y_rot) / 2) - z_rot)));
    result.colour = fdf.coordinate[y][x].colour;

    return (result);
}*/


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
