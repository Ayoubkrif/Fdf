/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:59:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/01 20:08:57 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

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

int	**fill_coordinate(t_list *lst)
{
	int		**coordinate;
	int		i;
	int		j;
	int		k;

	coordinate = ft_calloc(ft_lstsize(lst), sizeof(int *));
	i = 0;
	while (lst)
	{
		coordinate[i] = malloc(count_words(lst->s, " \n") * sizeof(int));
		j = 0;
		k = 0;
		while (j < count_words(lst->s, " \n"))
		{
			coordinate[i][j] = ft_atoi(&(lst->s)[k]);
			while (ft_isdigit((lst->s)[k]))
				k++;
			while ((lst->s)[k] == ' ' || (lst->s)[k] == '\n')
				k++;
			j++;
		}
		i++;
		lst = lst->next;
	}
	return (coordinate);
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

int	main(int argc, char **argv)
{
	int		**coordinate;
	char	*s;
	int		fd;
	t_list	*lst;

	(void)argc;
	lst = NULL;
	fd = open(argv[1], O_RDONLY);
	while (TRUE)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		ft_lstadd_back(&lst, ft_lstnew(s));
	}
	coordinate = fill_coordinate(lst);
	print_int_tab(coordinate, ft_lstsize(lst), 19);
	liberator_int_tab(coordinate, ft_lstsize(lst));
	ft_lstclear(&lst, free);
}
