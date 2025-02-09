/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:00:34 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/08 22:14:12 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "mlx.h"
#include "mlx_int.h"

void	put_new_img(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	recurse(*img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == KEY_Q)
	{
		img->option.angle.x += PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_A)
	{
		img->option.angle.x -= PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_W)
	{
		img->option.angle.y += PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_S)
	{
		img->option.angle.y -= PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_E)
	{
		img->option.angle.z += PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_D)
	{
		img->option.angle.z -= PI / 12;
		put_new_img(img);
	}
	if (keycode == KEY_0)
	{
		img->option.angle.x = 0;
		img->option.angle.y = 0;
		img->option.angle.z = 0;
		put_new_img(img);
	}
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_SPACE)
	{
		recurse(*img);
		mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	}
	if (keycode == KEY_UP)
	{
		img->option.translate.y += 10;
		put_new_img(img);
	}
	if (keycode == KEY_DOWN)
	{
		img->option.translate.y -= 10;
		put_new_img(img);
	}
	if (keycode == KEY_RIGHT)
	{
		img->option.translate.x += 10;
		put_new_img(img);
	}
	if (keycode == KEY_LEFT)
	{
		img->option.translate.x -= 10;
		put_new_img(img);
	}
	return (0);
}

int	translate_hook(int keycode, t_data *img)
{
	if (keycode == KEY_UP)
	{
		img->option.translate.y += 10;
		put_new_img(img);
	}
	if (keycode == KEY_DOWN)
	{
		img->option.translate.y -= 10;
		put_new_img(img);
	}
	if (keycode == KEY_RIGHT)
	{
		img->option.translate.x += 10;
		put_new_img(img);
	}
	if (keycode == KEY_LEFT)
	{
		img->option.translate.x -= 10;
		put_new_img(img);
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_data *fdf)
{
    (void)x;
    (void)y;
	if (button == MOUSE_WHEEL_UP)
	{
		fdf->option.zoom++;
		put_new_img(fdf);
	}
	else if (button == MOUSE_WHEEL_DOWN)
	{
		fdf->option.zoom--;
		put_new_img(fdf);
	}
	return (0);
}
