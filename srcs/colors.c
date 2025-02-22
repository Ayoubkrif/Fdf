/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:56:42 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 08:57:24 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

static int	find_color(t_data fdf, int base, int final, t_offset p)
{
	t_rgb	colora;
	t_rgb	colorb;
	t_rgb	color;
	float	ratio;

	if (fdf.coordinate[p.x][p.y].z <= fdf.z_min)
		return (base);
	if (fdf.coordinate[p.x][p.y].z >= fdf.z_max)
		return (final);
	ratio = (float)(fdf.coordinate[p.x][p.y].z - fdf.z_min) / \
		(fdf.z_max - fdf.z_min);
	colora.r = (base >> 16) & 0xFF;
	colora.g = (base >> 8) & 0xFF;
	colora.b = base & 0xFF;
	colorb.r = (final >> 16) & 0xFF;
	colorb.g = (final >> 8) & 0xFF;
	colorb.b = final & 0xFF;
	color.r = colora.r + (colorb.r - colora.r) * ratio;
	color.g = colora.g + (colorb.g - colora.g) * ratio;
	color.b = colora.b + (colorb.b - colora.b) * ratio;
	return ((color.r << 16) | (color.g << 8) | color.b);
}

/*void	change_base_color(t_data *fdf, int base, int up)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->coordinate.maxy)
	{
		j = 0;
		while (j < fdf->coordinate.maxx)
		{
			if (fdf->coordinate.map[i][j].color != 0xFFFFFF)
				fdf->coordinate.map[i][j].color = base;
			else
				fdf->coordinate.map[i][j].color = up; 
			j++;
		}
		i++;
	}
}*/

void	change_color(t_data *fdf, int base, int final)
{
	t_offset	p;

	p.x = 0;
	while (p.x < fdf->y_max)
	{
		p.y = 0;
		while (p.y < fdf->x_max)
		{
			fdf->coordinate[p.x][p.y].colour
				= find_color(*fdf, base, final, p);
			p.y++;
		}
		p.x++;
	}
}

void	set_earth_colors(int z, int *color)
{
	if (z <= -10)
		*color = DEEP_OCEAN;
	else if (z > -10 && z <= 0)
		*color = SHALLOW_WATER;
	else if (z > 0 && z <= 5)
		*color = SAND;
	else if (z > 5 && z <= 20)
		*color = GRASSLAND;
	else if (z > 20 && z <= 50)
		*color = HILLS;
	else if (z > 50 && z <= 100)
		*color = MOUNTAIN;
	else if (z > 100 && z <= 200)
		*color = HIGH_MOUNTAIN;
	else
		*color = SNOW;
}

void	earth_color(t_data *fdf)
{
	t_offset	p;

	p.y = 0;
	while (p.y < fdf->y_max)
	{
		p.x = 0;
		while (p.x < fdf->x_max)
		{
			set_earth_colors(fdf->coordinate[p.y][p.x].z,
				&fdf->coordinate[p.y][p.x].colour);
			p.x++;
		}
		p.y++;
	}
}

// void	move_z(t_data *fdf, int mode)
// {
// 	int	i;
// 	int	j;
//
// 	i = 0;
// 	while (i < fdf->coordinate.maxy)
// 	{
// 		j = 0;
// 		while (j < fdf->coordinate.maxx)
// 		{
// 			if (fdf->coordinate.map[i][j].z != fdf->coordinate.minz
// 				&& mode == 1)
// 				fdf->coordinate.map[i][j].z += 1;
// 			if (fdf->coordinate.map[i][j].z > fdf->coordinate.minz + 1
// 				&& mode == 0)
// 				fdf->coordinate.map[i][j].z -= 1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	if (mode == 1 && fdf->coordinate.minz + 1 != fdf->coordinate.maxz)
// 		fdf->coordinate.maxz += 1;
// 	if (mode == 0 && fdf->coordinate.minz + 1 != fdf->coordinate.maxz)
// 		fdf->coordinate.maxz -= 1;
// }

int	interpolate_color(int color1, int color2, float len, float pixel)
{
	int		red;
	int		green;
	int		blue;
	float	t;

	t = (len - pixel) / len;
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
