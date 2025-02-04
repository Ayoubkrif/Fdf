/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:12:18 by aykrifa           #+#    #+#             */
/*   Updated: 2024/09/25 10:12:21 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	testbase(char *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (tab[0] == '+' || tab[0] == '-' || tab[0] == ' '
		|| (tab[0] >= 9 && tab[0] <= 13))
		return (0);
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] == tab [j] || tab[j] == '-' || tab[j] == '+'
				|| tab[j] == ' ' || (tab[j] >= 9 && tab[j] <= 13))
				return (0);
			j++;
		}
	i++;
	}
	if (size < 2)
		return (0);
	return (1);
}

int	isbase(char c, char *base, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		if (c == base[i])
			return (i);
	i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int					i;
	int					s;
	int					r;
	unsigned int		size;

	size = ft_strlen(base);
	i = 0;
	r = 0;
	s = 1;
	if (testbase(base, size) == 0)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (isbase(str[i], base, size) != -1)
	{
		r = r * size;
		r = r + isbase(str[i++], base, size);
	}
	return (s * r);
}
/*
#include<unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	testbase1(char *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		if (tab[0] == '+' || tab[0] == '-')
			return (0);
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
	unsigned int	size;
	unsigned int	nb;

	size = 0;
	while (base[size])
		size++;
	if (testbase1(base, size) == 0)
		return ;
	if (nbr < 0)
	{	
		nb = -nbr;
		ft_putchar('-');
	}
	else
		nb = nbr;
	if (nb > size - 1)
	{
		ft_putnbr_base(nb / size, base);
	}
	ft_putchar(base[nb % size]);
}

int	main(int a, char **c)
{
	a = 2;
	ft_putnbr_base(ft_atoi_base(c[1],c[2]),c[2]);
	write(1, "\n",1);
	ft_putnbr_base(ft_atoi_base(c[1],c[2]),"0123456789");
}*/
