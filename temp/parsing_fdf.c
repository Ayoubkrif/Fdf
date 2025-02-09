/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:59:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/08 19:08:53 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	is_base(int c, char *base)
{
	while (*base)
	{
		if (c == *base)
			return (1);
		base++;
	}
	return (0);
}

static int	count_words(const char *s, char *c)
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

void	fill_coordinate(t_list *lst, t_data *fdf)
{
	int		i;
	int		j;
	int		k;

	fdf->coordinate = ft_calloc(ft_lstsize(lst), sizeof(t_coordinate *));
	i = 0;
	while (lst)
	{
		fdf->coordinate[i] = malloc(count_words(lst->s, " \n") * sizeof(t_coordinate));
		j = 0;
		k = 0;
		while (j < count_words(lst->s, " \n"))
		{
			fdf->coordinate[i][j].z = ft_atoi(&(lst->s)[k]);
			while (ft_isdigit((lst->s)[k]))
				k++;
			if ((!i && !j) || (fdf->coordinate[i][j].z > fdf->z_max))
				fdf->z_max = fdf->coordinate[i][j].z;
			if ((!i && !j) || (fdf->coordinate[i][j].z < fdf->z_min))
				fdf->z_min = fdf->coordinate[i][j].z;
			if (lst->s[k] == ',')
			{
				k += 3;
				fdf->coordinate[i][j].colour = ft_atoi_base(&(lst->s[k]), "0123456789ABCDEF");
				fdf->coordinate[i][j].colourh = ft_atoi_base(&(lst->s[k]), "0123456789abcdef");
				if (fdf->coordinate[i][j].colourh > fdf->coordinate[i][j].colour)
						fdf->coordinate[i][j].colour = fdf->coordinate[i][j].colourh;
				while (is_base(lst->s[k], "0123456789ABCDEFabcdef"))
					k++;
			}
			else
				fdf->coordinate[i][j].colour = 0x7f00ff;
			while ((lst->s)[k] == ' ' || (lst->s)[k] == '\n')
				k++;
			j++;
		}
		i++;
		lst = lst->next;
	}
	fdf->x_max = j;
	fdf->y_max = i;
}

void	liberator_int_tab(t_coordinate **tab, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

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
			printf("%4f ", tab[i][j].z);
			printf(",%8X", tab[i][j].colour);
			j++;
		}
		printf("\n");
		i++;
	}
}
