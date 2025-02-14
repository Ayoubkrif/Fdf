/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:00:34 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/14 10:13:16 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

int	view_hook(int keycode, t_data *img);
int	rotate_hook(int keycode, t_data *img);

int	key_hook(int keycode, t_data *img)
{
	if (keycode == KEY_ESC)
		exit_fdf(img);
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
		img->angle.x += PI_24;
		img->option.angle = set_new_angle(img->angle);
		put_new_img(img);
	}
	if (keycode == KEY_A)
	{
		img->angle.x -= PI_24;
		img->option.angle = set_new_angle(img->angle);
		put_new_img(img);
	}
	if (keycode == KEY_W)
	{
		img->angle.y += PI_24;
		img->option.angle = set_new_angle(img->angle);
		put_new_img(img);
	}
	if (keycode == KEY_S)
	{
		img->angle.y -= PI_24;
		img->option.angle = set_new_angle(img->angle);
		put_new_img(img);
	}
	if (keycode == KEY_E)
	{
		img->angle.z += PI_24;
		img->option.angle = set_new_angle(img->angle);
		put_new_img(img);
	}
	if (keycode == KEY_D)
	{
		img->angle.z -= PI_24;
		img->option.angle = set_new_angle(img->angle);
		put_new_img(img);
	}
	return (view_hook(keycode, img));
}

int	view_hook(int keycode, t_data *img)
{
	if (keycode == KEY_0)
	{
		img->angle.x = 0;
		img->angle.y = 0;
		img->angle.z = 0;
		img->option.angle = set_new_angle(img->angle);
		put_new_img(img);
	}
	return (0);
}
//int	colour_hook(int keycode, t_data *img){return (0);}
