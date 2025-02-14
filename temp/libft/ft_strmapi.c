/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:44:27 by ayoub             #+#    #+#             */
/*   Updated: 2024/11/09 11:03:00 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		i;
	char		*r;

	i = 0;
	while (s[i])
		i++;
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (r == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		r[i] = f((unsigned int)i, s[i]);
		i++;
	}
	r[i] = 0;
	return (r);
}
