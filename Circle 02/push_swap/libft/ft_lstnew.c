/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 11:00:03 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/23 11:17:46 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int num)
{
	t_list	*ret;

	ret = malloc(sizeof(t_list));
	if (ret == NULL)
		return (NULL);
	ret->num = num;
	ret->inst = 0;
	ret->next = NULL;
	return (ret);
}
