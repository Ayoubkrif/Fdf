/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 09:35:20 by aykrifa           #+#    #+#             */
/*   Updated: 2025/01/28 16:24:48 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cleanbuff(char *s, char *r)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (ft_strchr(s, '\n'))
	{
		while (s[i] != '\n' && i < BUFFER_SIZE)
			i++;
		if (s[i] == '\n')
			i++;
		while (s[i] && i < BUFFER_SIZE)
		{
			s[j] = s[i];
			i++;
			j++;
		}
	}
	while (j < BUFFER_SIZE)
		s[j++] = '\0';
	return (r);
}

int	initresult(char **r, char *s, int fd)
{
	if (fd < 0 && BUFFER_SIZE < 1 && read(fd, s, 0) < 0)
		return (0);
	*r = (char *)ft_calloc(sizeof(char), 1);
	if (!(*r))
		return (0);
	*r = ft_strjoin(*r, s, 1, 0);
	if (!(*r))
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	s[BUFFER_SIZE + 1] = {0};
	int			readbytes;
	char		*r;

	if (initresult(&r, s, fd) == 0)
		return (cleanbuff(s, NULL));
	if (ft_strchr(r, '\n'))
		return (cleanbuff(s, ft_substr(r, 0, ft_strchr(r, '\n') - r + 1, 1)));
	while (TRUE)
	{
		readbytes = read(fd, s, BUFFER_SIZE);
		if (readbytes < 1)
			break ;
		s[readbytes] = 0;
		r = ft_strjoin(r, s, 1, 0);
		if (!r)
			return (cleanbuff(s, NULL));
		if (ft_strchr(r, '\n'))
			return (cleanbuff(s, ft_substr(r, 0, ft_strchr(r, '\n')
						- r + 1, 1)));
	}
	if (r[0] && readbytes > -1)
		return (cleanbuff(s, r));
	return (free(r), cleanbuff(s, NULL));
}
