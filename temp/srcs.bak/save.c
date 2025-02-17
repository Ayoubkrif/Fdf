/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:31:59 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/16 21:45:07 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	restore_save(t_coordinate **from, t_coordinate **to, int xmax, int ymax)
{
	int	i;
	int	j;

	i = 0;
	while (i < ymax)
	{
		j = 0;
		while (j < xmax)
		{
			to[i][j].z = from[i][j].z;
			to[i][j].colour = from[i][j].colour;
			j++;
		}
	}
}

int	negative_interpolate(int color1, int color2, float t)
{
	int	red;
	int	green;
	int	blue;

	blue = 255 - ((color1 % 256) * (1 - t) + (color2 % 256) * t);
	color1 /= 256;
	color2 /= 256;
	green = 255 - ((color1 % 256) * (1 - t) + (color2 % 256) * t);
	green *= 256;
	color1 /= 256;
	color2 /= 256;
	red = 255 - ((color1 % 256) * (1 - t) + (color2 % 256) * t);
	red *= 256 * 256;
	return (red + green + blue);
}
