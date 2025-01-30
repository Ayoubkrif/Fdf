/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_windows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:43:34 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/30 13:18:26 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include "mlx.h"

int	main(int argc, char **argv)
{
	void	*mlx;

	mlx = mlx_init();
	mlx_new_window(mlx, 1920, 1080, "Fdf");
	mlx_loop(mlx);
	mlx_loop_end(mlx);
}
