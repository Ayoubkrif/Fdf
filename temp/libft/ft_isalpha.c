/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:38:17 by ayoub             #+#    #+#             */
/*   Updated: 2024/11/02 15:34:01 by ayoub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
/*#include<stdio.h>

int	main(int a, char **c)
{
    int i = 0;
    while (i <= 47)
    {
        printf("%d",ft_isalpha(i));
        i++;
    }
   i = 'A';
    while (i <= 'Z')
    {
        printf("%d",ft_isalpha(i));
        i++;
    }

}*/