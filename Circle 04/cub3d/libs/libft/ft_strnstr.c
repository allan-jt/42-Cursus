/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-guna <m3t9mm@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:07:19 by mal-guna          #+#    #+#             */
/*   Updated: 2021/09/29 18:19:44 by mal-guna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	counter;
	char	*b;

	b = (char *)big;
	counter = 0;
	if (little[0] == '\0')
		return (b);
	while (*b && len-- >= ft_strlen(little))
	{
		if (*b == little[counter])
		{
			if (ft_strncmp(b, little, ft_strlen(little)) == 0)
				return (b);
		}
		b++;
	}
	return (NULL);
}
