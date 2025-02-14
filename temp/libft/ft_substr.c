/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:42:41 by ayoub             #+#    #+#             */
/*   Updated: 2025/01/28 16:25:54 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len, int free_s)
{
	size_t			i;
	char			*r;
	unsigned int	smax;

	i = 0;
	smax = 0;
	while (s[smax])
		smax++;
	while (smax >= start && (s + start)[i] && i < len)
		i++;
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (!r)
		return (NULL);
	i = 0;
	while (smax >= start && (s + start)[i] && i < len)
	{
		r[i] = (s + start)[i];
		i++;
	}
	r[i] = '\0';
	if (free_s)
		free(s);
	return (r);
}
