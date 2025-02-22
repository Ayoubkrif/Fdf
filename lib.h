/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/22 10:08:26 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <math.h>
# include <sys/time.h>
# include "define.h"
# include "struct.h"

void			fill_coordinate(t_list *lst, t_data *fdf);
void			restore_save(t_coordinate **from, t_coordinate **to,
					int xmax, int ymax);
int				exit_fdf(t_data *fdf);
void			liberator_int_tab(t_coordinate **tab);
void			print_int_tab(t_coordinate **tab, int y, int x);
int				exit_fdf(t_data *fdf);
void			ft_exit(t_data *fdf, t_list *lst, int err_code);

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_projection	init_projection(int x, int y);
void			line(t_data *img, t_projection current,
					t_projection c, t_projection n);
t_projection	project_iso(t_coordinate point, int x, int y, t_option opt);

void			start_fdf(t_data *fdf);
t_offset		set_offset(t_data img);
t_angle			set_new_angle(t_vect angle);

void			put_new_img(t_data *img);

int				key_hook(int keycode, t_data *img);
void			clear_x_events(t_data *fdf);
void			change_color(t_data *fdf, int base, int final);
int				interpolate_color(int color1, int color2,
					float len, float pixel);
void			earth_color(t_data *fdf);

int				mouse_press(int button, int x, int y, t_data *fdf);
int				mouse_move(int x, int y, t_data *fdf);
int				mouse_release(int button, int x, int y, t_data *fdf);
time_t			get_time_in_ms(void);
////put_fdf.c///
void			put_from_0_0(t_data *fdf);
void			put_from_0_xmax(t_data *fdf);
void			put_from_ymax_0(t_data *fdf);
void			put_from_ymax_xmax(t_data *fdf);
////utils2.c////
float			distance(float a, float b);
t_projection	iv(int x, int y);
////wired_frame.c
void			set_wired_frame1(t_data *fdf,
					t_projection current, int x, int y);
void			set_wired_frame2(t_data *fdf,
					t_projection current, int x, int y);
void			set_wired_frame3(t_data *fdf,
					t_projection current, int x, int y);

#endif
