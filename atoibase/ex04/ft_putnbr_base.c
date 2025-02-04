/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:21:59 by aykrifa           #+#    #+#             */
/*   Updated: 2024/09/25 09:22:01 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	testbase(char *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (tab[0] == '-' || tab[0] == '+')
		return (0);
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] == tab [j] || tab[j] == '-' || tab[j] == '+')
				return (0);
			j++;
		}
	i++;
	}
	if (size < 2)
		return (0);
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	unsigned int		size;

	size = 0;
	while (base[size])
		size++;
	if (testbase(base, size) == 0)
		return ;
	if (nbr < 0)
	{	
		nbr = -nbr;
		ft_putchar('-');
	}
	if ((unsigned int)nbr > size - 1)
	{
		ft_putnbr_base(nbr / size, base);
	}
	ft_putchar(base[nbr % size]);
}
/*
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

int	main(int a, char **c)
{
	a = 2;
	ft_putnbr_base(ft_atoi(c[1]), c[2]);
}*/
