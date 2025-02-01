/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:42:46 by ayoub             #+#    #+#             */
/*   Updated: 2024/11/13 08:03:51 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	os;
	size_t	max;
	size_t	len;
	char	*r;

	os = 0;
	max = 0;
	while (isset(s1[os], set))
		os++;
	while (s1[max])
		max++;
	while (max > os && isset(s1[max - 1], set))
		max--;
	r = (char *)malloc((max - os + 1) * sizeof(char));
	if (!r)
		return (NULL);
	len = 0;
	while (len + os < max)
	{
		r[len] = s1[os + len];
		len++;
	}
	r[len] = 0;
	return (r);
}
