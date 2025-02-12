/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:00:34 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/12 18:05:48 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>

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
	if (keycode == KEY_Q || keycode == KEY_A
		|| keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_E || keycode == KEY_D)
	{
		if (keycode == KEY_A)
			img->angle.x -= PI_24;
		else if (keycode == KEY_Q)
			img->angle.x += PI_24;
		else if (keycode == KEY_S)
			img->angle.y -= PI_24;
		else if (keycode == KEY_W)
			img->angle.y += PI_24;
		else if (keycode == KEY_D)
			img->angle.z -= PI_24;
		else if (keycode == KEY_E)
			img->angle.z += PI_24;
		img->option.angle = set_new_angle(img->angle);
		put_new_img(img);
		return (0);
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

int	mouse_press(int button, int x, int y, t_data *fdf)
{
	struct timeval t;
	t_offset s;

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


	gettimeofday(&t, NULL);
	long elapsed_ms = (t.tv_sec - fdf->time.tv_sec) * 1000 +
                      (t.tv_usec - fdf->time.tv_usec) / 1000;
    if (elapsed_ms < 30)
        return (1);
    // Mettre à jour le dernier temps de clic
    fdf->time = t;
	if (button == 1)
    {
        s.x = x - 960;
        s.y = y - 540;

        // Rotation plus fluide : proportionnelle à la distance au centre
        fdf->angle.x += (s.x > 0) ? 0.01 : -0.01;
        fdf->angle.y += (s.y > 0) ? 0.01 : -0.01;

        put_new_img(fdf);
    }
	else if (button == 1)
    {
        s.x = x - 960;
        s.y = y - 540;

        if (s.x > 0)
            fdf->angle.x -= PI_24;
        else
            fdf->angle.x += PI_24;

        if (s.y > 0)
            fdf->angle.y -= PI_24;
        else
            fdf->angle.y += PI_24;

        put_new_img(fdf);
    }
	return (0);
}
