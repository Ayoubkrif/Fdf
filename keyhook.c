/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:00:34 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/07 14:24:29 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "mlx.h"
#include "mlx_int.h"

void	put_new_img(t_data *img)
{
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
	if (keycode == KEY_0)
	{
		img->angle.x = 0;
		img->angle.y = 0;
		img->angle.z = 0;
		put_new_img(img);
	}
	if (keycode == KEY_ESC) // Touche ESC pour quitter
		exit(0);
	if (keycode == KEY_SPACE) // Touche ESPACE pour lancer quadrillage
	{
		recurse(*img);
		mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	}
	if (keycode == KEY_UP)
	{
		img->translate.y += 10;
		put_new_img(img);
	}
	if (keycode == KEY_DOWN)
	{
		img->translate.y -= 10;
		put_new_img(img);
	}
	if (keycode == KEY_RIGHT)
	{
		img->translate.x += 10;
		put_new_img(img);
	}
	if (keycode == KEY_LEFT)
	{
		img->translate.x -= 10;
		put_new_img(img);
	}
	return (0);
}

int	translate_hook(int keycode, t_data *img)
{
	if (keycode == KEY_UP)
	{
		img->translate.y += 10;
		put_new_img(img);
	}
	if (keycode == KEY_DOWN)
	{
		img->translate.y -= 10;
		put_new_img(img);
	}
	if (keycode == KEY_RIGHT)
	{
		img->translate.x += 10;
		put_new_img(img);
	}
	if (keycode == KEY_LEFT)
	{
		img->translate.x -= 10;
		put_new_img(img);
	}
	return (0);
}

int mouse_press(int button, int x, int y, t_data *fdf)
{
    (void)x;
    (void)y;

	if (button == MOUSE_WHEEL_UP)
	{
		fdf->zoom++;
		put_new_img(fdf);
	}
	else if (button == MOUSE_WHEEL_DOWN)
	{
		fdf->zoom--;
		put_new_img(fdf);
	}
    return (0);
}


