/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 13:01:28 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/02 13:09:45 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*nxt;

	nxt = *lst;
	while (nxt != NULL)
	{
		current = nxt;
		nxt = nxt->next;
		(*del)(current->content);
		free(current);
	}
	*lst = NULL;
}
