/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wired_frame_option.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:01:52 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/22 10:02:05 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	set_wired_frame1(t_data *fdf, t_projection current, int x, int y)
{
	if (x + 1 < fdf->x_max)
		line(fdf, current, iv(x, y), iv(x + 1, y));
	if (y + 1 < fdf->y_max)
		line(fdf, current, iv(x, y), iv(x, y + 1));
}

void	set_wired_frame2(t_data *fdf, t_projection current, int x, int y)
{
	if (x + 1 < fdf->x_max && y + 1 < fdf->y_max)
		line(fdf, current, iv(x, y), iv(x + 1, y + 1));
	if (x + 1 < fdf->x_max && y - 1 >= 0)
		line(fdf, current, iv(x, y), iv(x + 1, y - 1));
}

void	set_wired_frame3(t_data *fdf, t_projection current, int x, int y)
{
	if (x + 1 < fdf->x_max && y - 2 >= 0)
		line(fdf, current, iv(x, y), iv(x + 1, y - 2));
	if (x - 1 >= 0 && y - 2 >= 0)
		line(fdf, current, iv(x, y), iv(x - 1, y - 2));
	if (x + 2 < fdf->x_max && y - 1 >= 0)
		line(fdf, current, iv(x, y), iv(x + 2, y - 1));
	if (x - 2 >= 0 && y - 1 >= 0)
		line(fdf, current, iv(x, y), iv(x - 2, y - 1));
}
