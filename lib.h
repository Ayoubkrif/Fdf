/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/17 22:53:59 by aykrifa          ###   ########.fr       */
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
# include "define.h"
# include "struct.h"

void			fill_coordinate(t_list *lst, t_data *fdf);
void			restore_save(t_coordinate **from, t_coordinate **to, int xmax, int ymax);
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
void			clear_x_events(t_data *fdf);
void			change_color(t_data *fdf, int base, int final);

int				mouse_press(int button, int x, int y, t_data *fdf);
int				mouse_move(int x, int y, t_data *fdf);
int				mouse_release(int button, int x, int y, t_data *fdf);
time_t			get_time_in_ms(void);

#endif
