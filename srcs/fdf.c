/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:59:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/16 13:55:22 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TO DO :
//			integrer les valeurs importantes a la structure :
//			x max, y max.
//			faire le projete en 2d
//			gerer les couleurs
//			d

#include "../lib.h"

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
}

void	init_fdf(int fd, t_list *map, t_data *fdf)
{
	map = init_map_lst(map, fd);
	if (!map)
		exit(0);
	fill_coordinate(map, fdf);
	ft_lstclear(&map, free);
	print_int_tab(fdf->coordinate, fdf->y_max, fdf->x_max);
	base_option_init(fdf);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "Square");
	fdf->img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->addr = mlx_get_data_addr(fdf->img,
			&fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	put_new_img(fdf);
}

int	exit_fdf(t_data *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	liberator_int_tab(fdf->coordinate, fdf->y_max);
	exit(15);
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
