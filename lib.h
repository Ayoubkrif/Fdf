/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/05 09:00:28 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_projection
{
	int	x;
	int	y;
	int	colour;
}	t_projection;

typedef struct s_coordinate
{
	int	z;
	int	colour;
	int	colourh;
}	t_coordinate;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	struct s_coordinate	**coordinate;
	int					y_max;
	int					x_max;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	struct s_projection	start;
}	t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

# define TRUE 1
# define OPEN_FAILURE -1

# define ANGLE 0.523598776
# define STEP 1
# define OFFSET 0

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
int				key_hook(int keycode, t_data *img);

#endif
