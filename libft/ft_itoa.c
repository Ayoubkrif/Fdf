/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:43:07 by ayoub             #+#    #+#             */
/*   Updated: 2024/11/13 07:50:44 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnb(long int nb, char **s, size_t i)
{
	if (nb < 0)
		nb = -nb;
	if (nb > 9)
		ft_putnb(nb / 10, s, i - 1);
	(*s)[i] = "0123456789"[nb % 10];
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*r;
	int		temp;

	size = 1;
	temp = n;
	while (temp > 9 || temp < (-9))
	{
		temp /= 10;
		size++;
	}
	if (n < 0)
		size++;
	r = (char *)malloc(sizeof(char) * (size + 1));
	if (!r)
		return (NULL);
	if (n < 0)
		r[0] = '-';
	ft_putnb(n, &r, size - 1);
	r[size] = 0;
	return (r);
}
