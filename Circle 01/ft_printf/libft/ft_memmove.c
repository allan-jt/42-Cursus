/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:35:37 by athekkep          #+#    #+#             */
/*   Updated: 2021/09/30 15:44:39 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;
	char	*dst;
	char	*sr;

	dst = (char *) dest;
	sr = (char *) src;
	i = -1;
	if (src != dest)
	{
		if (dst <= sr)
		{
			while (++i < len)
				dst[i] = sr[i];
		}
		else
		{
			while (len-- > 0)
				dst[len] = sr[len];
		}
	}
	return (dest);
}
