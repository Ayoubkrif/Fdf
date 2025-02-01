/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 08:21:01 by aykrifa           #+#    #+#             */
/*   Updated: 2024/11/15 12:01:16 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_mallocerror(void **content, void (*del)(void *))
{
	del(*content);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;
	void	*fcontent;

	fcontent = f(lst->content);
	head = ft_lstnew(fcontent);
	if (!head)
		return (ft_mallocerror(&fcontent, del));
	lst = lst->next;
	while (lst)
	{
		fcontent = f(lst->content);
		new = ft_lstnew(fcontent);
		if (new == NULL)
		{
			ft_lstclear(&head, del);
			return (ft_mallocerror(&fcontent, del));
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
