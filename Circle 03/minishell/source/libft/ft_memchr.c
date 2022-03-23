/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 15:57:41 by athekkep          #+#    #+#             */
/*   Updated: 2021/10/06 16:34:34 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*st;

	st = (void *) s;
	if (n <= 0)
		return (NULL);
	while (n-- > 0)
	{
		if (*st == (char) c)
			return ((void *) s);
		st++;
		s++;
	}
	return (NULL);
}
