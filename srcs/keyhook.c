/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:00:34 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/09 15:51:18 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

int	view_hook(int keycode, t_data *img);
int	rotate_hook(int keycode, t_data *img);

int	key_hook(int keycode, t_data *img)
{
	if (keycode == KEY_ESC)
	{
		liberator_int_tab(img->coordinate, img->y_max);
		mlx_destroy_image(img->mlx, img->img);
		exit(0);
	}
	return (translate_hook(keycode, img));
}

int	translate_hook(int keycode, t_data *img)
{
	if (keycode == KEY_UP)
	{
		img->option.translate.y -= 10;
		put_new_img(img);
	}
	if (keycode == KEY_DOWN)
	{
		img->option.translate.y += 10;
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
	return (rotate_hook(keycode, img));
}

int	rotate_hook(int keycode, t_data *img)
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
	return (view_hook(keycode, img));
}

int	view_hook(int keycode, t_data *img)
{
	if (keycode == KEY_0)
	{
		img->option.angle.x = 0;
		img->option.angle.y = 0;
		img->option.angle.z = 0;
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
