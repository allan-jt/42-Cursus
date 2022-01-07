/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:42:43 by athekkep          #+#    #+#             */
/*   Updated: 2021/09/30 15:41:40 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dst;
	char	*sr;

	i = 0;
	dst = dest;
	sr = (void *) src;
	while (n-- > 0 && dest != src)
	{
		dst[i] = sr[i];
		i++;
	}
	return (dest);
}
