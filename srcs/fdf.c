/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:59:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/18 15:39:23 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TO DO :
// rotation unique selon x y z
// translation
// scale

#include "../lib.h"
#include <stdlib.h>

static t_list	*init_map_lst(t_list *map, int fd)
{
	char	*s;

	while (TRUE)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		ft_lstadd_back(&map, ft_lstnew(s));
	}
	return (map);
}

static void	init_save(t_data *fdf)
{
	int				i;
	int				ymax;
	int				xmax;
	t_coordinate	**save;

	i = 0;
	ymax = fdf->y_max;
	xmax = fdf->x_max;
	save = ft_calloc(ymax + 1, sizeof(t_coordinate *));
	if (!save)
		return ;
	save[ymax] = NULL;
	while (i < ymax)
	{
		save[i] = ft_calloc(xmax, sizeof(t_coordinate));
		if (save[i] == NULL)
			return (liberator_int_tab(save));
		i++;
	}
	fdf->save = save;
}

static void	base_option_init(t_data *fdf)
{
	fdf->angle.x = 0.615;
	fdf->angle.y = -0.7853981634;
	fdf->angle.z = 0;
	fdf->option.angle = set_new_angle(fdf->angle);
	fdf->option.zoom = 10;
	fdf->option.translate.x = 0;
	fdf->option.translate.y = 0;
	fdf->mouse_pressed = 0;
	fdf->render_from = 0;
	fdf->time = get_time_in_ms();
	fdf->option.colour = 0;
}

void	init_fdf(int fd, t_list *map, t_data *fdf)
{
	map = init_map_lst(map, fd);
	fill_coordinate(map, fdf);
	ft_lstclear(&map, free);
	init_save(fdf);
	restore_save(fdf->coordinate, fdf->save, fdf->x_max, fdf->y_max);
	print_int_tab(fdf->coordinate, fdf->y_max, fdf->x_max);
	base_option_init(fdf);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, fdf->map);
	fdf->img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->addr = mlx_get_data_addr(fdf->img,
			&fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	put_new_img(fdf);
}

int	main(int argc, char **argv)
{
	t_data	fdf;
	int		fd;
	t_list	*map;

	map = NULL;
	if (argc < 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == OPEN_FAILURE)
		return (1);
	fdf.map = argv[1];
	init_fdf(fd, map, &fdf);
	close(fd);
	mlx_hook(fdf.win, 2, 1L << 0, key_hook, &fdf);
	mlx_hook(fdf.win, 17, 1L << 0, exit_fdf, &fdf);
	mlx_hook(fdf.win, 4, 1L << 2, mouse_press, &fdf);
	mlx_hook(fdf.win, 5, 1L << 3, mouse_release, &fdf);
	mlx_hook(fdf.win, 6, 1L << 6, mouse_move, &fdf);
	mlx_mouse_hook(fdf.win, mouse_press, &fdf);
	mlx_loop(fdf.mlx);
}
