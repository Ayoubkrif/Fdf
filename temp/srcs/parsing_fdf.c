/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:59:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/11 13:27:15 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

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

static int	skip_digits(char *s)
{
	int	k;

	k = 0;
	while (ft_isdigit(s[k]))
		k++;
	return (k);
}

static int	skip_whitespaces(char *s)
{
	int	k;

	k = 0;
	while (ft_isspace(s[k]))
		k++;
	return (k);
}

static int	set_color(char *s, int *result)
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

static void	set_min_and_max_z(t_data *fdf, int i, int j, int z)
{
	if ((!i && !j) || z > fdf->z_max)
		fdf->z_max = z;
	if ((!i && !j) || z < fdf->z_min)
		fdf->z_min = z;
}

void	fill_coordinate(t_list *lst, t_data *fdf)
{
	int		i;
	int		j;
	int		k;

	fdf->x_max = count_words(lst->s, " \n");
	fdf->y_max = ft_lstsize(lst);
	fdf->coordinate = ft_calloc(fdf->y_max, sizeof(t_coordinate *));
	if (!fdf->coordinate)
		exit(13);
	i = 0;
	while (lst)
	{
		fdf->coordinate[i] = malloc(fdf->x_max * sizeof(t_coordinate));
		if (!fdf->coordinate[i])
			exit(14);
		j = 0;
		k = 0;
		while (j < fdf->x_max)
		{
			fdf->coordinate[i][j].z = ft_atoi(&(lst->s)[k]);
			k += skip_digits(&lst->s[k]);
			set_min_and_max_z(fdf, i, j, fdf->coordinate[i][j].z);
			k += set_color(&lst->s[k], &fdf->coordinate[i][j].colour);
			k += skip_whitespaces(&lst->s[k]);
			j++;
		}
		i++;
		lst = lst->next;
	}
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
