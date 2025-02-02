/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:59:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/02 11:52:09 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

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

	fdf->coordinate = ft_calloc(ft_lstsize(lst), sizeof(int *));
	i = 0;
	while (lst)
	{
		fdf->coordinate[i] = malloc(count_words(lst->s, " \n") * sizeof(int));
		j = 0;
		k = 0;
		while (j < count_words(lst->s, " \n"))
		{
			fdf->coordinate[i][j] = ft_atoi(&(lst->s)[k]);
			while (ft_isdigit((lst->s)[k]))
				k++;
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

void	liberator_int_tab(int **tab, int line)
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

void	print_int_tab(int **tab, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%2d ", tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
