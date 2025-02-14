/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:44:11 by ayoub             #+#    #+#             */
/*   Updated: 2024/11/02 14:44:12 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*rep;

	if (s == NULL)
		return (NULL);
	len = 0;
	while (s[len])
		len++;
	rep = (char *)malloc((len + 1) * sizeof(char));
	if (!rep)
		return (NULL);
	i = 0;
	while (i < len)
	{
		rep[i] = s[i];
		i++;
	}
	rep[i] = '\0';
	return (rep);
}
