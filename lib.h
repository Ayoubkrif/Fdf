/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/16 17:11:05 by aykrifa          ###   ########.fr       */
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
# include <sys/time.h>

typedef struct s_projection
{
	int	x;
	int	y;
	int		colour;
}	t_projection;

typedef struct s_coordinate
{
	int	z;
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
	int					zoom;
	t_angle				angle;
	int				colour;
}	t_option;

typedef struct s_data
{
	char				*map;
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;

	t_coordinate	**coordinate;

	float				y_max;
	float				x_max;
	float				z_max;
	float				z_min;
	t_vect				angle;
	t_option			option;
	int					mouse_pressed;
	int					render_from;
	time_t				time;

	int					bits_per_pixel;
	int					line_length;
	int					endian;
}	t_data;

# define OPEN_FAILURE -1

# define BASE_COLOR 0xffffff
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
# define KEY_C           99
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
# define KEY_PLUS 61
# define KEY_MINUS 45
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5

# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_MOUSE_PRESS 4
# define EVENT_MOUSE_RELEASE 5
# define EVENT_DESTROY 17

# define PI_12 0.261799388
# define PI_24 0.130899694

# define WAIT 0
# define READY 1
# define UP_LEFT 0
# define UP_RIGHT 1
# define DOWN_LEFT 2
# define DOWN_RIGHT 3
void			fill_coordinate(t_list *lst, t_data *fdf);
void			liberator_int_tab(t_coordinate **tab, int line);
void			print_int_tab(t_coordinate **tab, int y, int x);
int				exit_fdf(t_data *fdf);

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_draw_line_b(t_data *data, int x1, int y1, int x2, int y2, int color1, int color2);
void			ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);
t_projection	init_projection(int x, int y);
void			line(t_data *img, t_projection current, t_projection c, t_projection n);
t_projection	project_iso(t_coordinate point, int x, int y, t_option opt);

void			start_fdf(t_data *fdf);
t_offset		set_offset(t_data img);
t_angle			set_new_angle(t_vect angle);

void			put_new_img(t_data *img);

int				key_hook(int keycode, t_data *img);

int				mouse_press(int button, int x, int y, t_data *fdf);
int				mouse_move(int x, int y, t_data *fdf);
int				mouse_release(int button, int x, int y, t_data *fdf);
time_t			get_time_in_ms(void);

#endif
