/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:59:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/04 12:36:57 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TO DO :
//			integrer les valeurs importantes a la structure :
//			x max, y max.
//			faire le projete en 2d
//			gerer les couleurs
//			d

#include "lib.h"
#include "mlx.h"

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

void	init_fdf(int fd, t_list *map, t_data *fdf)
{
	map = init_map_lst(map, fd);
	fill_coordinate(map, fdf);
	print_int_tab(fdf->coordinate, fdf->y_max, fdf->x_max);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "Square");
	fdf->img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
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
	mlx_key_hook(fdf.win, (int (*)(int , void *))key_hook, &fdf);
	mlx_loop(fdf.mlx);
	liberator_int_tab(fdf.coordinate, fdf.y_max);
	ft_lstclear(&map, free);
}
