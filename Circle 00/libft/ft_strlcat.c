/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athekkep <athekkep@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:24:44 by athekkep          #+#    #+#             */
/*   Updated: 2021/09/30 09:09:39 by athekkep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;
	size_t	count;

	i = ft_strlen(dst);
	count = ft_strlen(src);
	len = i;
	if (len > dstsize)
		return (count + dstsize);
	if (dstsize - len > 0)
	{
		while (*src != '\0' && i < (dstsize - 1))
		{
			dst[i++] = *src;
			src++;
		}	
	}
	dst[i] = '\0';
	return (len + count);
}
