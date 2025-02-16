/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:12:50 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/16 21:52:59 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

int	mouse_press(int button, int x, int y, t_data *fdf)
{
	(void)x;
	(void)y;
	if (button == 1)
		fdf->mouse_pressed = 1;
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

int	mouse_move(int x, int y, t_data *fdf)
{
	if (fdf->mouse_pressed)
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
	if (button == 1)
		fdf->mouse_pressed = 0;
	return (0);
}
