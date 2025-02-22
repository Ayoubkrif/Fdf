/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 10:22:41 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

t_projection	init_projection(int x, int y)
{
	t_projection	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_projection	project_iso(t_coordinate point, int x, int y, t_option opt)
{
	t_projection	result;
	t_vect			rot;
	float			tmp;

	rot.y = opt.angle.cos_x * y - opt.angle.sin_x * point.z;
	rot.z = opt.angle.sin_x * y + opt.angle.cos_x * point.z;
	rot.x = opt.angle.cos_y * x + opt.angle.sin_y * rot.z;
	rot.z = -opt.angle.sin_y * x + opt.angle.cos_y * rot.z;
	tmp = rot.x;
	rot.x = opt.angle.cos_z * rot.x - opt.angle.sin_z * rot.y;
	rot.y = opt.angle.sin_z * tmp + opt.angle.cos_z * rot.y;
	result.x = opt.translate.x + opt.offset.x + (opt.zoom * rot.x);
	result.y = opt.translate.y + opt.offset.y + (opt.zoom * rot.y);
	result.colour = point.colour;
	return (result);
}

t_projection	project_3d_to_2d(int x, int y, int z, t_option opt)
{
	t_projection	result;
	t_vect			rot;
	float			tmp;

	rot.y = opt.angle.cos_x * y - opt.angle.sin_x * z;
	rot.z = opt.angle.sin_x * y + opt.angle.cos_x * z;
	rot.x = opt.angle.cos_y * x + opt.angle.sin_y * rot.z;
	rot.z = -opt.angle.sin_y * x + opt.angle.cos_y * rot.z;
	tmp = rot.x;
	rot.x = opt.angle.cos_z * rot.x - opt.angle.sin_z * rot.y;
	rot.y = opt.angle.sin_z * tmp + opt.angle.cos_z * rot.y;
	result.x = (opt.zoom * rot.x);
	result.y = (opt.zoom * rot.y);
	return (result);
}

t_offset	set_offset(t_data img)
{
	t_offset		offset;
	t_projection	middle;

	middle = project_3d_to_2d(img.x_max / 2, img.y_max / 2,
			distance(img.z_max, img.z_min), img.option);
	offset.x = ((float)WINX / 2) - middle.x;
	offset.y = ((float)WINY / 2) - middle.y;
	return (offset);
}
