/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:53:00 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/23 20:31:17 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_projection
{
	double		x;
	double		y;
	int			colour;
}	t_projection;

typedef struct s_index
{
	int		x;
	int		y;
}	t_index;

typedef struct s_coordinate
{
	int		z;
	int		colour;
}	t_coordinate;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}	t_vect;

typedef struct s_angle
{
	float	cos_x;
	float	sin_x;
	float	cos_y;
	float	sin_y;
	float	cos_z;
	float	sin_z;
}	t_angle;

typedef struct s_offset
{
	int	x;
	int	y;
}	t_offset;

typedef struct s_option
{
	t_offset		offset;
	t_offset		translate;
	int				zoom;
	t_angle			angle;
	int				colour;
}	t_option;

typedef struct s_data
{
	char				*map_name;
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;

	t_coordinate		**coordinate;
	t_coordinate		**save;

	int					y_max;
	int					x_max;
	float				z_max;
	float				z_min;
	t_vect				angle;
	t_option			option;
	int					mouse_pressed;
	int					render_from;
	int					render_quality;

	int					bits_per_pixel;
	int					line_length;
	int					endian;
}	t_data;

#endif
