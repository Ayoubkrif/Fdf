/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:41:44 by ayoub             #+#    #+#             */
/*   Updated: 2025/01/22 12:01:50 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_join(char *s1, char *s2, char **r)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		(*r)[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		(*r)[i + j] = s2[j];
		j++;
	}
	(*r)[i + j] = '\0';
}

char	*ft_strjoin(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*r;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	r = (char *)malloc(sizeof(char) * (1 + i + j));
	if (!r)
		return (NULL);
	ft_join(s1, s2, &r);
	if (free_s1 != 0)
		free(s1);
	if (free_s2)
		free(s2);
	return (r);
}
