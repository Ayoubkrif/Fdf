/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:55:43 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/20 14:57:39 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_round(double num)
{
	int	rounded;

	rounded = (int)num;
	if (num - rounded >= .5)
		rounded++;
	return (rounded);
}

float	distance(int a, int b)
{
	return ((a + b) / 2);
}
