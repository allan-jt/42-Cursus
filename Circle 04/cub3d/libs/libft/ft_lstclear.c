/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:16:01 by mal-guna          #+#    #+#             */
/*   Updated: 2021/10/03 16:16:13 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		del(tmp2->content);
		free(tmp2);
	}
	*lst = NULL;
}
