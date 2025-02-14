/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:44:06 by ayoub             #+#    #+#             */
/*   Updated: 2024/11/12 13:51:22 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	words;
	size_t	k;

	i = 0;
	words = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
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

static void	fall(char ***dest, size_t i)
{
	while (i > 0)
	{
		i--;
		free((*dest)[i]);
	}
	free(*dest);
	*dest = NULL;
}

static void	mallocall(char ***dest, const char *str, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (i < count_words(str, c))
	{
		k = 0;
		while (str[j] == c)
			j++;
		while (str[j + k] != c && str[j + k])
			k++;
		(*dest)[i] = (char *)malloc(sizeof(char) * (k + 1));
		if ((*dest)[i] == 0)
		{
			fall(dest, i);
			return ;
		}
		j += k;
		i++;
	}
}

static void	filldest(char ***dest, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (i < count_words(s, c))
	{
		k = 0;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
		{
			(*dest)[i][k] = s[j];
			k++;
			j++;
		}
		(*dest)[i][k] = '\0';
		i++;
	}
}

char	**ft_split(const char *s, char c)
{
	char	**dest;

	dest = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (dest == NULL)
		return (NULL);
	mallocall(&dest, s, c);
	if (dest == NULL)
		return (NULL);
	filldest(&dest, s, c);
	dest[count_words(s, c)] = 0;
	return (dest);
}
