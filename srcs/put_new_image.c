/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_new_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:28:19 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/20 14:49:59 by aykrifa          ###   ########.fr       */
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

void	put_new_img(t_data *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->addr = mlx_get_data_addr(fdf->img,
			&fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	start_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
