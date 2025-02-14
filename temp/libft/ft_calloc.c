/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 07:47:50 by aykrifa           #+#    #+#             */
/*   Updated: 2024/11/14 14:17:20 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*rep;
	size_t	i;

	if (nmemb && size > 2147483647 / nmemb)
		return (NULL);
	i = 0;
	rep = malloc(nmemb * size);
	if (!rep)
		return (NULL);
	while (i < nmemb * size)
		((unsigned char *)rep)[i++] = 0;
	return (rep);
}
