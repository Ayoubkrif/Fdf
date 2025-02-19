/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:51 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/19 10:14:14 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

int	count_words(const char *s, char *c)
{
	int	i;
	int	words;
	int	k;

	i = 0;
	words = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c[0] || s[i] == c[1])
			k = 0;
		else if (k == 0)
		{
			words++;
			k = 1;
		}
		i++;
	}
	return (words);
}

int	skip_digits(char *s)
{
	int	k;

	k = 0;
	while (ft_isdigit(s[k]))
		k++;
	return (k);
}

int	skip_whitespaces(char *s)
{
	int	k;

	k = 0;
	while (ft_isspace(s[k]))
		k++;
	return (k);
}

int	set_color(char *s, int *result)
{
	int	colour;
	int	k;

	k = 0;
	if (s[k] == ',')
	{
		k += 3;
		*result = ft_atoi_base(&s[k], "0123456789ABCDEF");
		colour = ft_atoi_base(&s[k], "0123456789abcdef");
		if (colour > *result)
			*result = colour;
		while (is_base(s[k], "0123456789ABCDEFabcdef") != -1)
			k++;
	}
	else
		*result = BASE_COLOR;
	return (k);
}

void	set_min_and_max_z(t_data *fdf, int i, int j, int z)
{
	if ((!i && !j) || z > fdf->z_max)
		fdf->z_max = z;
	if ((!i && !j) || z < fdf->z_min)
		fdf->z_min = z;
}
