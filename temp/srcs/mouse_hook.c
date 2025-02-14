/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:12:50 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/14 11:50:08 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

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
	else if (button == 1) // Clic gauche enfoncé
		fdf->mouse_pressed = 1;
	return (0);
}

int	mouse_move(int x, int y, t_data *fdf)
{
	time_t	now;

	now = get_time_in_ms();
	if (now - fdf->time < 60)
		return (0);
	fdf->time = now;
	if (fdf->mouse_pressed) // Si clic gauche maintenu
	{
		fdf->option.translate.x = x - 960;
		fdf->option.translate.y = y - 540;
		put_new_img(fdf);
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_data *fdf)
{
	(void)x;
	(void)y;

	if (button == 1) // Relâchement du clic gauche
		fdf->mouse_pressed = 0;
	return (0);
}
