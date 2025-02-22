/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:38:03 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/22 10:43:13 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void	liberator_int_tab(t_coordinate **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

int	exit_fdf(t_data *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	liberator_int_tab(fdf->coordinate);
	liberator_int_tab(fdf->save);
	exit(0);
}

void	ft_exit(t_data *fdf, t_list *lst, int err_code)
{
	if (lst)
		ft_lstclear(&lst, free);
	liberator_int_tab(fdf->coordinate);
	liberator_int_tab(fdf->save);
	if (fdf->mlx)
	{
		free(fdf->mlx);
		if (fdf->img)
			mlx_destroy_image(fdf->mlx, fdf->img);
		if (fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		mlx_destroy_display(fdf->mlx);
	}
	exit(err_code);
}
