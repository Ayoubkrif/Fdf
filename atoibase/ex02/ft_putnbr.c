/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:26:56 by aykrifa           #+#    #+#             */
/*   Updated: 2024/09/24 18:26:58 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{	
		nb = -nb;
		ft_putchar('-');
	}	
	if (nb > 9)
	{
		ft_putnbr((nb / 10));
	}
	ft_putchar((nb % 10) + 48);
}
/*
int	main(void)
{
	ft_putnbr(-2147483648);
}*/
