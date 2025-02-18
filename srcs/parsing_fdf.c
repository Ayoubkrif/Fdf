/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:59:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/18 16:27:10 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"
#include <time.h>

int		count_words(const char *s, char *c);
int		skip_digits(char *s);
int		skip_whitespaces(char *s);
int		set_color(char *s, int *result);
void	set_min_and_max_z(t_data *fdf, int i, int j, int z);

void	calloc_rows_set_max(t_list *lst, t_data *fdf)
{
	fdf->y_max = ft_lstsize(lst);
	if (fdf->y_max == 0)
		ft_exit(fdf, lst, EXIT_FAILURE);
	fdf->x_max = count_words(lst->s, " \n");
	if (fdf->x_max == 0 || fdf->x_max == -1)
		ft_exit(fdf, lst, EXIT_FAILURE);
	fdf->save = NULL;
	fdf->coordinate = ft_calloc(fdf->y_max + 1, sizeof(t_coordinate *));
	if (!fdf->coordinate)
		exit(1);
	fdf->coordinate[(int)fdf->y_max] = NULL;
}

int	skip_digits_space_coma_hex(int i, int *j, char *s, t_data *fdf)
{
	int	k;

	k = 0;
	k += skip_digits(&s[k]);
	k += set_color(&s[k], &fdf->coordinate[i][*j].colour);
	k += skip_whitespaces(&s[k]);
	*j = *j + 1;
	return (k);
}

void	fill_coordinate(t_list *lst, t_data *fdf)
{
	int		i;
	int		j;
	int		k;
	t_list	*current;

	current = lst;
	i = 0;
	calloc_rows_set_max(lst, fdf);
	while (current)
	{
		fdf->coordinate[i] = malloc(fdf->x_max * sizeof(t_coordinate));
		if (!fdf->coordinate[i])
			ft_exit(fdf, lst, EXIT_FAILURE);
		j = 0;
		k = 0;
		while (j < fdf->x_max)
		{
			k += skip_whitespaces(&current->s[k]);
			fdf->coordinate[i][j].z = ft_atoi(&(current->s)[k]);
			set_min_and_max_z(fdf, i, j, fdf->coordinate[i][j].z);
			k += skip_digits_space_coma_hex(i, &j, &current->s[k], fdf);
		}
		i++;
		current = current->next;
	}
}
