/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:28:27 by aykrifa           #+#    #+#             */
/*   Updated: 2024/09/24 18:28:29 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int	i;
	int	s;
	int	r;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10;
		r = r + str[i] - '0';
		i++;
	}
	return (s * r);
}
/*
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

int	main(int a, char **c)
{
	a = 2;
	ft_putnbr(ft_atoi(c[1]));
}*/
