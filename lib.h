/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:48 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/01 21:40:18 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		**coordinate;
	int		y_max;
	int		x_max;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_projection
{
	int	i;
	int	j;
}	t_projection;

# define TRUE 1
# define OPEN_FAILURE -1

int	**fill_coordinate(t_list *lst);
void	liberator_int_tab(int **tab, int line);
void	print_int_tab(int **tab, int y, int x);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
// Algorithme de Bresenham
void ft_draw_line_b(t_data *data, int x1, int y1, int x2, int y2, int color);
//algo qui fonctionne
void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);
t_projection	init_point(int	x, int	y);
void	line(t_data img, t_point current, t_point next, int coulour);
void	recurse(t_data img, t_point current, t_point end);
void	quadrillage(t_data img, t_point start, int n_x, int n_y);
int	key_hook(int keycode, t_data *img);

#endif
