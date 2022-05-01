/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <mal-guna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:03:36 by mal-guna          #+#    #+#             */
/*   Updated: 2021/10/04 01:52:11 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	n;
	size_t	max;

	max = ft_strlen(dst) + ft_strlen(src);
	n = 0;
	i = 0;
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	else if (size > ft_strlen(dst))
		max = ft_strlen(src) + ft_strlen(dst);
	while (dst[i])
		i++;
	while (src[n] && i < (size - 1))
	{
		dst[i] = src[n];
		n++;
		i++;
	}
	dst[i] = '\0';
	return (max);
}
