/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:11:56 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/02 15:14:54 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*newnode;
	t_list	*newliststart;

	current = lst;
	newliststart = NULL;
	while (current != NULL)
	{
		newnode = ft_lstnew((*f)(current->content));
		if (newnode == NULL)
		{	
			ft_lstclear(&newliststart, del);
			return (NULL);
		}
		ft_lstadd_back(&newliststart, newnode);
		current = current->next;
	}
	return (newliststart);
}
