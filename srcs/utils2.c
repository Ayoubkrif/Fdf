/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:55:43 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/22 09:15:23 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

float	distance(float a, float b)
{
	return ((a + b) / 2);
}

t_projection	iv(int x, int y)
{
	t_projection	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_angle	set_new_angle(t_vect angle)
{
	t_angle	result;

	result.cos_x = cos(angle.x);
	result.sin_x = sin(angle.x);
	result.cos_y = cos(angle.y);
	result.sin_y = sin(angle.y);
	result.cos_z = cos(angle.z);
	result.sin_z = sin(angle.z);
	return (result);
}
