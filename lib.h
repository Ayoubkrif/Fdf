/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/09 14:18:08 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>

typedef struct s_projection
{
	float	x;
	float	y;
	int		colour;
}	t_projection;

typedef struct s_coordinate
{
	float	z;
	int		colour;
	int		colourh;
}	t_coordinate;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}	t_vect;

typedef struct s_offset
{
	float	x;
	float	y;
}	t_offset;

typedef struct s_option
{
	t_offset		offset;
	t_offset		translate;
	int					zoom;
	t_vect				angle;
}	t_option;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;

	t_coordinate	**coordinate;

	float				y_max;
	float				x_max;
	float				z_max;
	float				z_min;
	t_option			option;

	int					bits_per_pixel;
	int					line_length;
	int					endian;
}	t_data;


# define TRUE 1
# define OPEN_FAILURE -1

# define ANGLE 0.523598776
# define STEP 1
# define OFFSET 500
# define PI 3.14159265358979323846
# define KEY_ESC         65307
# define KEY_W           119
# define KEY_A           97
# define KEY_S           115
# define KEY_D           100
# define KEY_Q           113
# define KEY_E           101
# define KEY_UP          65362
# define KEY_DOWN        65364
# define KEY_LEFT        65361
# define KEY_RIGHT       65363
# define KEY_PLUS        61
# define KEY_MINUS       45
# define KEY_1           49
# define KEY_2           50
# define KEY_3           51
# define KEY_4           52
# define KEY_5           53
# define KEY_6           54
# define KEY_7           55
# define KEY_8           56
# define KEY_9           57
# define KEY_0           48
# define KEY_SPACE       32
# define KEY_SHIFT       65505
# define KEY_CTRL        65507
# define KEY_ALT         65513
// Clavier principal
# define KEY_PLUS 61        // '+' sur clavier AZERTY
# define KEY_MINUS 45       // '-' sur clavier AZERTY

// Molette de la souris
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5

// Événements MLX
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_MOUSE_PRESS 4
# define EVENT_MOUSE_RELEASE 5
# define EVENT_DESTROY 17

void			fill_coordinate(t_list *lst, t_data *fdf);
void			liberator_int_tab(t_coordinate **tab, int line);
void			print_int_tab(t_coordinate **tab, int y, int x);

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
// Algorithme de Bresenham
//void			ft_draw_line_b(t_data *data, int x1, int y1, int x2, int y2, int color);
void			ft_draw_line_b(t_data *data, int x1, int y1, int x2, int y2, int color1, int color2);
//algo qui fonctionne
void			ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);
//void			ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);
t_projection	init_projection(int x, int y);
//void			line(t_data img, t_projection current, t_projection next, int coulour);
void			line(t_data img, t_projection current, t_projection next, int xc, int yc, int xn, int yn);
//void			recurse(t_data img, t_projection current, t_projection end);
void			recurse(t_data img);
//void			quadrillage(t_data img, t_projection start, int n_x, int n_y);
void			quadrillage(t_data img);

void			put_new_img(t_data *img);
int				key_hook(int keycode, t_data *img);
int				mouse_press(int button, int x, int y, t_data *fdf);
int				translate_hook(int keycode, t_data *img);

#endif
