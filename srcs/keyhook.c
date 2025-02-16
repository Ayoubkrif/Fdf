/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:00:34 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/16 16:49:02 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

static int	translate_hook(int keycode, t_data *img)
{
	if (keycode == KEY_UP)
		img->option.translate.y -= 10;
	else if (keycode == KEY_DOWN)
		img->option.translate.y += 10;
	else if (keycode == KEY_RIGHT)
		img->option.translate.x += 10;
	else if (keycode == KEY_LEFT)
		img->option.translate.x -= 10;
	return (keycode == KEY_LEFT
		|| keycode == KEY_RIGHT
		|| keycode == KEY_UP
		|| keycode == KEY_DOWN);
}

static int	rotate_hook(int keycode, t_data *img)
{
	if (keycode == KEY_Q)
		img->angle.x += PI_24;
	else if (keycode == KEY_A)
		img->angle.x -= PI_24;
	else if (keycode == KEY_W)
		img->angle.y += PI_24;
	else if (keycode == KEY_S)
		img->angle.y -= PI_24;
	else if (keycode == KEY_E)
		img->angle.z += PI_24;
	else if (keycode == KEY_D)
		img->angle.z -= PI_24;
	return (keycode == KEY_Q
		|| keycode == KEY_A
		|| keycode == KEY_W
		|| keycode == KEY_S
		|| keycode == KEY_E
		|| keycode == KEY_D);
}

static int	view_hook(int keycode, t_data *img)
{
	if (keycode == KEY_0)
	{
		img->angle.x = 0;
		img->angle.y = 0;
		img->angle.z = 0;
	}
	if (keycode == KEY_SPACE)
	{
		if (img->render_from == 3)
			img->render_from = 0;
		else
			img->render_from++;
		printf("current render_from : %d\n",img->render_from);
	}
	return (keycode == KEY_0 || keycode == KEY_SPACE);
}

int	colour_hook(int keycode, t_data *fdf)
{
	if (keycode == KEY_C)
	{
		if (fdf->option.colour == 2)
			fdf->option.colour = 0;
		else
			fdf->option.colour++;
	}
	return (keycode == KEY_C);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == KEY_ESC)
		exit_fdf(img);
	if (rotate_hook(keycode, img)
		|| translate_hook(keycode, img)
		|| view_hook(keycode, img)
		|| colour_hook(keycode, img))
	{
		img->option.angle = set_new_angle(img->angle);
		put_new_img(img);
	}
	return (0);
}
