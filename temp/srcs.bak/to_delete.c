/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:21:40 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/16 13:24:10 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	print_int_tab(t_coordinate **tab, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%4i ", tab[i][j].z);
			printf(",%8X", tab[i][j].colour);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_header(t_data *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 50, 50, 0xFFFFFF,"caca : <X>");
}

void	erase_image(t_data *fdf)
{
	ft_memset(fdf->img, 0, (1920 * 1080 * sizeof(int)));
}

time_t    get_time_in_ms(void)
{
    struct timeval    tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
