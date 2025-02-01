/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:44:20 by ayoub             #+#    #+#             */
/*   Updated: 2024/11/13 07:59:53 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size - 1 && size)
		i++;
	while (dst[i])
		i++;
	while (src[j] && i + j < size - 1 && size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (size > i)
		dst[i + j] = '\0';
	while (src[j])
		j++;
	if (size <= i)
		return (j + size);
	return (i + j);
}
