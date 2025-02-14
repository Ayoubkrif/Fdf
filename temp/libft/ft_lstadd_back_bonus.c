/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:43:18 by ayoub             #+#    #+#             */
/*   Updated: 2025/01/28 10:27:49 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newnode)
{
	t_list	*current;

	current = *lst;
	if (*lst == NULL)
	{
		*lst = newnode;
		(*lst)->next = NULL;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = newnode;
}
