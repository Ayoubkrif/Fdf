/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:54:25 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/11 08:58:00 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

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
