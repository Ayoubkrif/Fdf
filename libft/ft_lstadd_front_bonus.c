/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:43:22 by ayoub             #+#    #+#             */
/*   Updated: 2025/01/28 10:28:34 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *newnode)
{
	if (!newnode)
		return ;
	if (!(*lst))
	{
		newnode->next = NULL;
		*lst = newnode;
		return ;
	}
	newnode->next = *lst;
	*lst = newnode;
}
